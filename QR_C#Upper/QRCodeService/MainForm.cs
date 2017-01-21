using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using ZXing;
using ZXing.Common;
using ZXing.QrCode;
//视频命名空间
using AForge;
using AForge.Video;
using AForge.Video.DirectShow;
using System.IO.Ports;//必须加载串口的命名空间
using System.IO;//文件系统必须加载

namespace QRCodeService
{
    public partial class MainForm : Form
    {
        //摄像头对象
        private Capture cam;
        private FilterInfoCollection videoDevices;
        //计时器
        System.Timers.Timer _timer = null;
        //扫描时间频率(毫秒)
        private int scanTime = 250;
        private bool videoState = false;
        private IContainer componentss;
        //串口对象实例化
        public SerialPort serialPort1 = new SerialPort();
        private Thread threadreview;
        private Thread threaddisplay;
        private Thread threaddisplaysend;
        private string reviewdate;
        private int ThreadSwitchFlag;
        private long received_count = 0;//接收计数
        private long send_count = 0;//发送计数
        private bool Listening = false;//是否没有执行完invoke相关操作
        private StringBuilder builder = new StringBuilder();//避免在事件处理方法中反复的创建，定义到外面。
        private bool Closing = false;//是否正在关闭串口，执行Application.DoEvents，并阻止再次invoke
        public MainForm()
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            InitializeComponent();
            pictureBox1.Visible = false;
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            string[] comname = SerialPort.GetPortNames();
            Array.Sort(comname);
            comboBox_com.Items.AddRange(comname);
            comboBox_com.SelectedIndex = comboBox_com.Items.Count > 0 ? 0 : -1;
            comboBox_bort.SelectedIndex = comboBox_bort.Items.Count > 0 ? 2 : -1;
            comboBox_stop.SelectedIndex = comboBox_stop.Items.Count > 0 ? 0 : -1;
            comboBox_data.SelectedIndex = comboBox_data.Items.Count > 0 ? 0 : -1;
            comboBox_check.SelectedIndex = comboBox_check.Items.Count > 0 ? 0 : -1;
            //初始化状态参数
            toolStripStatusLabel9.Text = "串口号：" + comboBox_com.Text + " |";
            toolStripStatusLabel2.Text = "波特率：" + comboBox_bort.Text + " |";
            toolStripStatusLabel8.Text = "Rx：" + received_count.ToString() + " |";
            toolStripStatusLabel7.Text = "Tx：" + send_count.ToString() + " |";
            toolStripStatusLabel6.Text = DateTime.Now.ToString() + " |";
            toolStripStatusLabel3.Text = "停止位：" + comboBox_stop.Text + " |";
            toolStripStatusLabel4.Text = "数据位：" + comboBox_data.Text + " |";
            toolStripStatusLabel5.Text = "检验位：" + comboBox_check.Text + " |";
            serialPort1.DataReceived += port_DataRecerived;//添加事件，特别重要！！！
            try
            {
                // 枚举所有视频输入设备
                videoDevices = new FilterInfoCollection(FilterCategory.VideoInputDevice);

                if (videoDevices.Count == 0)
                    throw new ApplicationException();
                foreach (FilterInfo device in videoDevices)
                {
                    comboBox3.Items.Add(device.Name);
                }
                comboBox3.SelectedIndex = 0;
            }
            catch (ApplicationException)
            {
                comboBox3.Items.Add("No local capture devices");
                videoDevices = null;
            }
        }

        //点击开始扫描
        private void btnStart_Click(object sender, EventArgs e)
        {
            if (button_camera.Text == "开始扫描")
            {
                button_camera.Text = "停止扫描";
                Console.WriteLine("摄像头启动");
                StartCam();
                if (_timer != null && _timer.Enabled)
                {
                    _timer.Stop();
                    _timer.Dispose();
                }
                //定时器启动，设置扫描频率
                _timer = new System.Timers.Timer(scanTime);
                _timer.Start();
                _timer.Elapsed += new System.Timers.ElapsedEventHandler(_timer_Elapsed);
            }
            else
            {
                button_camera.Text = "开始扫描";
                Console.WriteLine("摄像头关闭");
                textBoxMsg1.Text = string.Empty;
                //摄像头停止
                StopCam();
                //计时器循环扫描停止
                _timer.Stop();
                _timer.Dispose();
            }
        }

        //定时器工作
        void _timer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            Console.WriteLine("扫描开始");
            try
            {
                //摄像头截屏
                string result = SnapShot();
                if (string.IsNullOrEmpty(result))
                {

                    if (pictureBox1.Image == null)
                    {
                        return;
                    }
                    else
                    {
                        try
                        {
                            result = RQDecode(new Bitmap(pictureBox1.Image));
                            Console.WriteLine(result);
                        }
                        catch (Exception ss)
                        { }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
            Console.WriteLine("扫描结束");

        }

        //--截图
        private string SnapShot()
        {
            Cursor.Current = Cursors.WaitCursor;
            if (m_ip != IntPtr.Zero)
            {
                Marshal.FreeCoTaskMem(m_ip);
                m_ip = IntPtr.Zero;
            }

            m_ip = cam.Click();
            Bitmap b = new Bitmap(cam.Width, cam.Height, cam.Stride, PixelFormat.Format24bppRgb, m_ip);

            b.RotateFlip(RotateFlipType.RotateNoneFlipY);
            b = ResizeImage(b, pictureBox1);
            pictureBox1.Image = b;

            Bitmap bit = null;
            bit = new Bitmap(pictureBox1.Width, pictureBox1.Height);

            Graphics g = Graphics.FromImage(bit);
            g.CopyFromScreen(this.PointToScreen(pictureBox1.Location), new System.Drawing.Point(0, 0), bit.Size);
            g.Dispose();
            string result = string.Empty;
            try
            {
                //扫描二维码
                result = RQDecode(bit);
                Console.WriteLine(result);
            }
            catch (Exception ex)
            {
                
            }
            if (!string.IsNullOrEmpty(result))
            {
                //显示二维码值
                textBoxMsg1.Text = result;
                if (serialPort1.IsOpen)
                {
                    switch (result)
                    {
                        case "11111": WriteByteToSerialPort(0x05, 0x0b); break;
                        case "22222": WriteByteToSerialPort(0x05, 0x0c); break;
                        case "33333": WriteByteToSerialPort(0x05, 0x0d); break;
                        case "44444": WriteByteToSerialPort(0x05, 0x0e); break;
                        case "55555": WriteByteToSerialPort(0x05, 0x0b); break;
                        case "66666": WriteByteToSerialPort(0x05, 0x0c); break;
                        default: break;
                    }
                }
            }
            Cursor.Current = Cursors.Default;
            return result;
        }

        //--重置图像大小
        private Bitmap ResizeImage(Bitmap bmp, PictureBox picBox)
        {
            float xRate = (float)bmp.Width / picBox.Size.Width;
            float yRate = (float)bmp.Height / picBox.Size.Height;
            if (xRate <= 1 && yRate <= 1)
            {
                return bmp;
            }
            else
            {
                float tRate = (xRate >= yRate) ? xRate : yRate;
                Graphics g = null;
                try
                {
                    int newW = (int)(bmp.Width / tRate);
                    int newH = (int)(bmp.Height / tRate);
                    Bitmap b = new Bitmap(newW, newH);
                    g = Graphics.FromImage(b);
                    g.InterpolationMode = InterpolationMode.HighQualityBicubic;
                    g.DrawImage(bmp, new Rectangle(0, 0, newW, newH), new Rectangle(0, 0, bmp.Width, bmp.Height), GraphicsUnit.Pixel);
                    g.Dispose();
                    return b;
                }
                catch
                {
                    return null;
                }
                finally
                {
                    if (null != g)
                    {
                        g.Dispose();
                    }
                }
            }
        }

        //--解码
        private string RQDecode(Bitmap img)
        {
            string errText = string.Empty;
            Result result = null;
            if (img != null)
            {
                try
                {
                    result = new BarcodeReader().Decode(img);
                }
                catch { return errText; }
                if (result != null)
                {
                    return result.Text;
                }
                else
                {
                    return errText;
                }
            }
            else
            {
                return errText;
            }
        }

        //--开启摄像头
        private void StartCam()
        {
            const int VIDEODEVICE = 0;
            const int VIDEOWIDTH = 640;
            const int VIDEOHEIGHT = 480;
            const int VIDEOBITSPERPIXEL = 32;
            try
            {
                cam = new Capture(VIDEODEVICE, VIDEOWIDTH, VIDEOHEIGHT, VIDEOBITSPERPIXEL, pictureBox2);
                videoState = true;
            }
            catch { }
        }

        //--停止摄像头
        private void StopCam()
        {
            cam.Dispose();
            if (m_ip != IntPtr.Zero)
            {
                Marshal.FreeCoTaskMem(m_ip);
                m_ip = IntPtr.Zero;
            }
            videoState = false;
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            PictureBox p = (PictureBox)sender;
            Pen pp = new Pen(System.Drawing.Color.Red);
            e.Graphics.DrawRectangle(pp, e.ClipRectangle.X, e.ClipRectangle.Y, e.ClipRectangle.X + e.ClipRectangle.Width - 1, e.ClipRectangle.Y + e.ClipRectangle.Height - 1);

        }

        private void MainForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            try
            {
                StopCam();
            }
            catch{ }
            try
            {
                Dispose();
            }
            catch{ }
        }

        private void button_com_Click(object sender, EventArgs e)
        {
            if (comboBox_com.Text == "")
                MessageBox.Show("未检测到串口！", "提示");
            else
            {
                if (!serialPort1.IsOpen)
                {
                    button_search.Enabled = false;
                    button_start.Text = "关闭串口";
                    try
                    {
                        serialPort1.PortName = comboBox_com.Text;
                        serialPort1.BaudRate = Convert.ToInt32(comboBox_bort.Text);
                        switch (comboBox_stop.Text)
                        {
                            case "1": serialPort1.StopBits = StopBits.One; break;
                            case "2": serialPort1.StopBits = StopBits.Two; break;
                            default: serialPort1.StopBits = StopBits.OnePointFive; break;
                        }
                        serialPort1.DataBits = Convert.ToInt32(comboBox_data.Text);
                        switch (comboBox_check.Text)
                        {
                            case "无": serialPort1.Parity = Parity.None; break;
                            case "奇校验": serialPort1.Parity = Parity.Odd; break;
                            case "偶校验": serialPort1.Parity = Parity.Even; break;
                            default: break;
                        }
                        serialPort1.Open();
                        //ThreadSwitchFlag = 1;
                        //threadreview = new Thread(serialport_review);
                        ////threaddisplay = new Thread(display_review);
                        //threadreview.Start();
                        ////threaddisplay.Start();
                    }
                    catch (Exception er)
                    {
                        MessageBox.Show(er.ToString(), "提示");
                    }
                }
                else
                {
                    button_search.Enabled = true;
                    button_start.Text = "打开串口";
                    try
                    {
                        //threadreview.Abort();
                        ////threaddisplay.Abort();
                        //ThreadSwitchFlag = 0;
                        serialPort1.Close();
                    }
                    catch (Exception er)
                    {
                        MessageBox.Show(er.ToString(), "提示");
                    }
                }
            }
        }

        /******************************串口接收事件******************************************/
        private void port_DataRecerived(object sender, SerialDataReceivedEventArgs e)
        {
            if (Closing) return;
            try
            {
                uint ultrasonic;
                //int n = serialPort1.BytesToRead; //记录下缓冲区的字节个数 
                byte[] buf = new byte[4]; //声明一个临时数组存储当前来的串口数据
                serialPort1.Read(buf, 0, 4); //读取缓冲数据到buf中，同时将这串数据从缓冲区移除 
                //string str = string.Concat(buf[1]);//转换为字符串型
                builder.Clear();
                received_count++;
                //toolStripStatusLabel4.Text = "Rx:" + received_count.ToString() + " |";
                if ((buf[0] == 0x00) && (buf[3] == 0xff))
                {
                    ultrasonic = buf[1];
                    ultrasonic = ultrasonic << 8;
                    ultrasonic = ultrasonic | buf[2];
                    //this.Invoke((EventHandler)(delegate
                    //{
                    //    textBox1.Text = ultrasonic.ToString();//长度为1补0
                    //}));
                    this.textBox1.Invoke(new MethodInvoker(delegate
                    {
                        this.textBox1.Text = ultrasonic.ToString();//长度为1补0
                    }));
                }
                else if ((buf[0] == 0x01) && (buf[3] == 0xfe))
                {
                    ultrasonic = buf[1];
                    ultrasonic = ultrasonic << 8;
                    ultrasonic = ultrasonic | buf[2];
                    this.textBox2.Invoke(new MethodInvoker(delegate
                    {
                        this.textBox2.Text = ultrasonic.ToString();
                    }));
                }
                else if ((buf[0] == 0x02) && (buf[3] == 0xfd))
                {
                    ultrasonic = buf[1];
                    ultrasonic = ultrasonic << 8;
                    ultrasonic = ultrasonic | buf[2];
                    this.textBox3.Invoke(new MethodInvoker(delegate
                    {
                        this.textBox3.Text = ultrasonic.ToString();
                    }));
                }
                else if ((buf[0] == 0x03) && (buf[3] == 0xfc))
                {
                    ultrasonic = buf[1];
                    ultrasonic = ultrasonic << 8;
                    ultrasonic = ultrasonic | buf[2];
                    this.textBox4.Invoke(new MethodInvoker(delegate
                    {
                        this.textBox4.Text = ultrasonic.ToString();
                    }));
                }
                else if ((buf[0] == 0x04) && (buf[3] == 0xfb))
                {
                    ultrasonic = buf[1];
                    ultrasonic = ultrasonic << 8;
                    ultrasonic = ultrasonic | buf[2];
                    this.textBox5.Invoke(new MethodInvoker(delegate
                    {
                        this.textBox5.Text = ultrasonic.ToString();
                    }));
                }
                else
                {
                    //MessageBox.Show("数据接收失败，请检查！", "提示");
                    if (button_start.Text == "关闭串口")
                        serialPort1.DiscardInBuffer();//清空接收缓存区
                }
            }
            finally { Listening = false; }
        }

        /*****************************************接收函数*****************************************/
        private void serialport_review()
        {
            try
            {
                uint ultrasonic;
                //int n = serialPort1.BytesToRead; //记录下缓冲区的字节个数 
                byte[] buf = new byte[4]; //声明一个临时数组存储当前来的串口数据
                serialPort1.Read(buf, 0, 4); //读取缓冲数据到buf中，同时将这串数据从缓冲区移除 
                //string str = string.Concat(buf[1]);//转换为字符串型
                received_count++;
                toolStripStatusLabel4.Text = "Rx:" + received_count.ToString() + " |";
                if ((buf[0] == 0x00) && (buf[3] == 0xff))
                {
                    ultrasonic = buf[1];
                    ultrasonic = ultrasonic << 8;
                    ultrasonic = ultrasonic | buf[2];
                    //this.Invoke((EventHandler)(delegate
                    //{
                    //    textBox1.Text = ultrasonic.ToString();//长度为1补0
                    //}));
                    this.textBox1.Invoke(new MethodInvoker(delegate
                    {
                        this.textBox1.Text = ultrasonic.ToString();//长度为1补0
                    }));
                }
                else if ((buf[0] == 0x01) && (buf[3] == 0xfe))
                {
                    ultrasonic = buf[1];
                    ultrasonic = ultrasonic << 8;
                    ultrasonic = ultrasonic | buf[2];
                    this.textBox2.Invoke(new MethodInvoker(delegate
                    {
                        this.textBox2.Text = ultrasonic.ToString();
                    }));
                }
                else if ((buf[0] == 0x02) && (buf[3] == 0xfd))
                {
                    ultrasonic = buf[1];
                    ultrasonic = ultrasonic << 8;
                    ultrasonic = ultrasonic | buf[2];
                    this.textBox3.Invoke(new MethodInvoker(delegate
                    {
                        this.textBox3.Text = ultrasonic.ToString();
                    }));
                }
                else if ((buf[0] == 0x03) && (buf[3] == 0xfc))
                {
                    ultrasonic = buf[1];
                    ultrasonic = ultrasonic << 8;
                    ultrasonic = ultrasonic | buf[2];
                    this.textBox4.Invoke(new MethodInvoker(delegate
                    {
                        this.textBox4.Text = ultrasonic.ToString();
                    }));
                }
                else if ((buf[0] == 0x04) && (buf[3] == 0xfb))
                {
                    ultrasonic = buf[1];
                    ultrasonic = ultrasonic << 8;
                    ultrasonic = ultrasonic | buf[2];
                    this.textBox5.Invoke(new MethodInvoker(delegate
                    {
                        this.textBox5.Text = ultrasonic.ToString();
                    }));
                }
                else
                {
                    //MessageBox.Show("数据接收失败，请检查！", "提示");
                    if (button_start.Text == "关闭串口")
                        serialPort1.DiscardInBuffer();//清空接收缓存区
                }
            }
            catch { }

        }

        /**********************************串口发送协议***************************************/
        public void WriteByteToSerialPort(byte hearder, byte data)
        {
            byte[] Buffer = new byte[3] { hearder, data, hearder };
            Buffer[2] = (byte)~hearder;
            if (serialPort1.IsOpen)
            {
                try
                {
                    serialPort1.Write(Buffer, 0, 3);
                    send_count++;
                    toolStripStatusLabel5.Text = "Tx：" + send_count.ToString() + " |";
                    if (button_start.Text == "关闭串口")
                    {
                        send_count++;
                        toolStripStatusLabel5.Text = "Tx：" + send_count.ToString() + " |";
                    }
                }
                catch
                {
                    MessageBox.Show("发送错误，请检查！", "提示");
                }
            }
        }

        /*********************************按钮事件******************************************/
        private void button4_Click(object sender, EventArgs e)
        {
            WriteByteToSerialPort(0x00, 0x01);//腰部-
        }

        private void button5_Click(object sender, EventArgs e)
        {
            WriteByteToSerialPort(0x00, 0x02);//腰部+
        }

        private void button3_Click(object sender, EventArgs e)
        {
            WriteByteToSerialPort(0x01, 0x03);//大臂-
        }

        private void button6_Click(object sender, EventArgs e)
        {
            WriteByteToSerialPort(0x01, 0x04);//大臂+
        }

        private void button7_Click(object sender, EventArgs e)
        {
            WriteByteToSerialPort(0x02, 0x05);//小臂-
        }

        private void button14_Click(object sender, EventArgs e)
        {
            WriteByteToSerialPort(0x02, 0x06);//小臂+
        }

        private void button10_Click(object sender, EventArgs e)
        {
            WriteByteToSerialPort(0x03, 0x07);//手腕-
        }

        private void button11_Click(object sender, EventArgs e)
        {
            WriteByteToSerialPort(0x03, 0x08);//手腕+
        }

        private void button12_Click(object sender, EventArgs e)
        {
            WriteByteToSerialPort(0x04, 0x09);//手爪+
        }

        private void button15_Click(object sender, EventArgs e)
        {
            WriteByteToSerialPort(0x04, 0x0a);//手爪-
        }

        private void timer_now_Tick(object sender, EventArgs e)
        {
            toolStripStatusLabel6.Text = DateTime.Now.ToString() + " |";
        }

        private void comboBox_com_TextChanged(object sender, EventArgs e)
        {
            toolStripStatusLabel9.Text = "串口号：" + comboBox_com.Text + " |";
        }

        private void comboBox_bort_TextChanged(object sender, EventArgs e)
        {
            serialPort1.BaudRate = Convert.ToInt32(comboBox_bort.Text);
            toolStripStatusLabel2.Text = "波特率：" + comboBox_bort.Text + " |";
        }

        private void comboBox_stop_TextChanged(object sender, EventArgs e)
        {
            switch (comboBox_stop.Text)
            {
                case "1": serialPort1.StopBits = StopBits.One; break;
                case "2": serialPort1.StopBits = StopBits.Two; break;
                default: serialPort1.StopBits = StopBits.OnePointFive; break;
            }
            toolStripStatusLabel3.Text = "停止位：" + comboBox_stop.Text + " |";
        }

        private void comboBox_data_TextChanged(object sender, EventArgs e)
        {
            serialPort1.DataBits = Convert.ToInt32(comboBox_data.Text);
            toolStripStatusLabel4.Text = "数据位：" + comboBox_data.Text + " |";
        }

        private void comboBox_check_TextChanged(object sender, EventArgs e)
        {
            switch (comboBox_check.Text)
            {
                case "无": serialPort1.Parity = Parity.None; break;
                case "奇校验": serialPort1.Parity = Parity.Odd; break;
                case "偶校验": serialPort1.Parity = Parity.Even; break;
                default: break;
            }
            toolStripStatusLabel5.Text = "检验位：" + comboBox_check.Text + " |";
        }

        /************************************扫描到新的二维码*************************************/
        private void textBoxMsg1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
