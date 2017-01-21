using System;
using System.Runtime.InteropServices;
namespace QRCodeService
{
    partial class MainForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        IntPtr m_ip = IntPtr.Zero;
        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (componentss != null)
                {
                    componentss.Dispose();
                }
            }
            base.Dispose(disposing);
            if (m_ip != IntPtr.Zero)
            {
                Marshal.FreeCoTaskMem(m_ip);
                m_ip = IntPtr.Zero;
            }
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.button_camera = new System.Windows.Forms.Button();
            this.textBoxMsg1 = new System.Windows.Forms.TextBox();
            this.label_QRCode = new System.Windows.Forms.Label();
            this.button_start = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label_check = new System.Windows.Forms.Label();
            this.label_data = new System.Windows.Forms.Label();
            this.comboBox_check = new System.Windows.Forms.ComboBox();
            this.comboBox_data = new System.Windows.Forms.ComboBox();
            this.comboBox_stop = new System.Windows.Forms.ComboBox();
            this.label_stop = new System.Windows.Forms.Label();
            this.button_search = new System.Windows.Forms.Button();
            this.comboBox3 = new System.Windows.Forms.ComboBox();
            this.comboBox_bort = new System.Windows.Forms.ComboBox();
            this.comboBox_com = new System.Windows.Forms.ComboBox();
            this.label_camera = new System.Windows.Forms.Label();
            this.label_boad = new System.Windows.Forms.Label();
            this.label_com = new System.Windows.Forms.Label();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.button10 = new System.Windows.Forms.Button();
            this.button11 = new System.Windows.Forms.Button();
            this.button12 = new System.Windows.Forms.Button();
            this.button14 = new System.Windows.Forms.Button();
            this.button15 = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.pictureBox4 = new System.Windows.Forms.PictureBox();
            this.toolStripStatusLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel3 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel4 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel5 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel6 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel7 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel8 = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel9 = new System.Windows.Forms.ToolStripStatusLabel();
            this.timer_now = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).BeginInit();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.pictureBox1.Location = new System.Drawing.Point(245, 74);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(457, 405);
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            // 
            // pictureBox2
            // 
            this.pictureBox2.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.pictureBox2.Location = new System.Drawing.Point(245, 74);
            this.pictureBox2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(457, 405);
            this.pictureBox2.TabIndex = 0;
            this.pictureBox2.TabStop = false;
            // 
            // button_camera
            // 
            this.button_camera.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_camera.Location = new System.Drawing.Point(147, 180);
            this.button_camera.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button_camera.Name = "button_camera";
            this.button_camera.Size = new System.Drawing.Size(63, 23);
            this.button_camera.TabIndex = 2;
            this.button_camera.Text = "开始扫描";
            this.button_camera.UseVisualStyleBackColor = true;
            this.button_camera.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // textBoxMsg1
            // 
            this.textBoxMsg1.Location = new System.Drawing.Point(21, 457);
            this.textBoxMsg1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBoxMsg1.Multiline = true;
            this.textBoxMsg1.Name = "textBoxMsg1";
            this.textBoxMsg1.Size = new System.Drawing.Size(211, 22);
            this.textBoxMsg1.TabIndex = 4;
            this.textBoxMsg1.TextChanged += new System.EventHandler(this.textBoxMsg1_TextChanged);
            // 
            // label_QRCode
            // 
            this.label_QRCode.AutoSize = true;
            this.label_QRCode.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_QRCode.Location = new System.Drawing.Point(17, 434);
            this.label_QRCode.Name = "label_QRCode";
            this.label_QRCode.Size = new System.Drawing.Size(107, 20);
            this.label_QRCode.TabIndex = 6;
            this.label_QRCode.Text = "二维码扫描结果";
            // 
            // button_start
            // 
            this.button_start.Location = new System.Drawing.Point(9, 180);
            this.button_start.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button_start.Name = "button_start";
            this.button_start.Size = new System.Drawing.Size(63, 23);
            this.button_start.TabIndex = 7;
            this.button_start.Text = "打开串口";
            this.button_start.UseVisualStyleBackColor = true;
            this.button_start.Click += new System.EventHandler(this.button_com_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label_check);
            this.groupBox1.Controls.Add(this.label_data);
            this.groupBox1.Controls.Add(this.comboBox_check);
            this.groupBox1.Controls.Add(this.comboBox_data);
            this.groupBox1.Controls.Add(this.comboBox_stop);
            this.groupBox1.Controls.Add(this.label_stop);
            this.groupBox1.Controls.Add(this.button_search);
            this.groupBox1.Controls.Add(this.button_camera);
            this.groupBox1.Controls.Add(this.comboBox3);
            this.groupBox1.Controls.Add(this.button_start);
            this.groupBox1.Controls.Add(this.comboBox_bort);
            this.groupBox1.Controls.Add(this.comboBox_com);
            this.groupBox1.Controls.Add(this.label_camera);
            this.groupBox1.Controls.Add(this.label_boad);
            this.groupBox1.Controls.Add(this.label_com);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox1.Size = new System.Drawing.Size(219, 211);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "设置";
            // 
            // label_check
            // 
            this.label_check.AutoSize = true;
            this.label_check.Location = new System.Drawing.Point(7, 131);
            this.label_check.Name = "label_check";
            this.label_check.Size = new System.Drawing.Size(53, 12);
            this.label_check.TabIndex = 15;
            this.label_check.Text = "校检位：";
            // 
            // label_data
            // 
            this.label_data.AutoSize = true;
            this.label_data.Location = new System.Drawing.Point(7, 104);
            this.label_data.Name = "label_data";
            this.label_data.Size = new System.Drawing.Size(53, 12);
            this.label_data.TabIndex = 14;
            this.label_data.Text = "数据位：";
            // 
            // comboBox_check
            // 
            this.comboBox_check.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_check.FormattingEnabled = true;
            this.comboBox_check.Items.AddRange(new object[] {
            "无",
            "奇校验",
            "偶校验"});
            this.comboBox_check.Location = new System.Drawing.Point(78, 128);
            this.comboBox_check.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.comboBox_check.Name = "comboBox_check";
            this.comboBox_check.Size = new System.Drawing.Size(133, 20);
            this.comboBox_check.TabIndex = 13;
            this.comboBox_check.TextChanged += new System.EventHandler(this.comboBox_check_TextChanged);
            // 
            // comboBox_data
            // 
            this.comboBox_data.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_data.FormattingEnabled = true;
            this.comboBox_data.Items.AddRange(new object[] {
            "8",
            "7",
            "6",
            "5"});
            this.comboBox_data.Location = new System.Drawing.Point(78, 101);
            this.comboBox_data.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.comboBox_data.Name = "comboBox_data";
            this.comboBox_data.Size = new System.Drawing.Size(133, 20);
            this.comboBox_data.TabIndex = 12;
            this.comboBox_data.TextChanged += new System.EventHandler(this.comboBox_data_TextChanged);
            // 
            // comboBox_stop
            // 
            this.comboBox_stop.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_stop.FormattingEnabled = true;
            this.comboBox_stop.Items.AddRange(new object[] {
            "1",
            "1.5",
            "2"});
            this.comboBox_stop.Location = new System.Drawing.Point(78, 74);
            this.comboBox_stop.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.comboBox_stop.Name = "comboBox_stop";
            this.comboBox_stop.Size = new System.Drawing.Size(133, 20);
            this.comboBox_stop.TabIndex = 11;
            this.comboBox_stop.TextChanged += new System.EventHandler(this.comboBox_stop_TextChanged);
            // 
            // label_stop
            // 
            this.label_stop.AutoSize = true;
            this.label_stop.Location = new System.Drawing.Point(7, 77);
            this.label_stop.Name = "label_stop";
            this.label_stop.Size = new System.Drawing.Size(53, 12);
            this.label_stop.TabIndex = 10;
            this.label_stop.Text = "停止位：";
            // 
            // button_search
            // 
            this.button_search.Location = new System.Drawing.Point(78, 180);
            this.button_search.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button_search.Name = "button_search";
            this.button_search.Size = new System.Drawing.Size(63, 23);
            this.button_search.TabIndex = 9;
            this.button_search.Text = "扫描串口";
            this.button_search.UseVisualStyleBackColor = true;
            // 
            // comboBox3
            // 
            this.comboBox3.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox3.FormattingEnabled = true;
            this.comboBox3.Location = new System.Drawing.Point(78, 154);
            this.comboBox3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.comboBox3.Name = "comboBox3";
            this.comboBox3.Size = new System.Drawing.Size(133, 20);
            this.comboBox3.TabIndex = 5;
            // 
            // comboBox_bort
            // 
            this.comboBox_bort.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_bort.FormattingEnabled = true;
            this.comboBox_bort.Items.AddRange(new object[] {
            "2400",
            "4800",
            "9600",
            "14400",
            "19200",
            "38400",
            "43000",
            "57600",
            "76800",
            "115200",
            "128000"});
            this.comboBox_bort.Location = new System.Drawing.Point(78, 45);
            this.comboBox_bort.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.comboBox_bort.Name = "comboBox_bort";
            this.comboBox_bort.Size = new System.Drawing.Size(133, 20);
            this.comboBox_bort.TabIndex = 4;
            this.comboBox_bort.TextChanged += new System.EventHandler(this.comboBox_bort_TextChanged);
            // 
            // comboBox_com
            // 
            this.comboBox_com.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_com.FormattingEnabled = true;
            this.comboBox_com.Location = new System.Drawing.Point(78, 18);
            this.comboBox_com.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.comboBox_com.Name = "comboBox_com";
            this.comboBox_com.Size = new System.Drawing.Size(133, 20);
            this.comboBox_com.TabIndex = 3;
            this.comboBox_com.TextChanged += new System.EventHandler(this.comboBox_com_TextChanged);
            // 
            // label_camera
            // 
            this.label_camera.AutoSize = true;
            this.label_camera.Location = new System.Drawing.Point(7, 157);
            this.label_camera.Name = "label_camera";
            this.label_camera.Size = new System.Drawing.Size(65, 12);
            this.label_camera.TabIndex = 2;
            this.label_camera.Text = "视频设备：";
            // 
            // label_boad
            // 
            this.label_boad.AutoSize = true;
            this.label_boad.Location = new System.Drawing.Point(7, 48);
            this.label_boad.Name = "label_boad";
            this.label_boad.Size = new System.Drawing.Size(53, 12);
            this.label_boad.TabIndex = 1;
            this.label_boad.Text = "波特率：";
            // 
            // label_com
            // 
            this.label_com.AutoSize = true;
            this.label_com.Location = new System.Drawing.Point(7, 21);
            this.label_com.Name = "label_com";
            this.label_com.Size = new System.Drawing.Size(53, 12);
            this.label_com.TabIndex = 0;
            this.label_com.Text = "串口号：";
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(79, 57);
            this.button3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(64, 21);
            this.button3.TabIndex = 11;
            this.button3.Text = "大臂(上)";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(79, 29);
            this.button4.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(64, 22);
            this.button4.TabIndex = 12;
            this.button4.Text = "腰部(左)";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(149, 29);
            this.button5.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(64, 22);
            this.button5.TabIndex = 13;
            this.button5.Text = "腰部(右)";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(149, 57);
            this.button6.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(64, 21);
            this.button6.TabIndex = 14;
            this.button6.Text = "大臂(下)";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(149, 82);
            this.button7.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(64, 24);
            this.button7.TabIndex = 15;
            this.button7.Text = "小臂(下)";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // button10
            // 
            this.button10.Location = new System.Drawing.Point(149, 110);
            this.button10.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button10.Name = "button10";
            this.button10.Size = new System.Drawing.Size(64, 22);
            this.button10.TabIndex = 18;
            this.button10.Text = "手腕(右)";
            this.button10.UseVisualStyleBackColor = true;
            this.button10.Click += new System.EventHandler(this.button10_Click);
            // 
            // button11
            // 
            this.button11.Location = new System.Drawing.Point(79, 110);
            this.button11.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button11.Name = "button11";
            this.button11.Size = new System.Drawing.Size(64, 22);
            this.button11.TabIndex = 19;
            this.button11.Text = "手腕(左)";
            this.button11.UseVisualStyleBackColor = true;
            this.button11.Click += new System.EventHandler(this.button11_Click);
            // 
            // button12
            // 
            this.button12.Location = new System.Drawing.Point(149, 136);
            this.button12.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(64, 27);
            this.button12.TabIndex = 20;
            this.button12.Text = "手爪(合)";
            this.button12.UseVisualStyleBackColor = true;
            this.button12.Click += new System.EventHandler(this.button12_Click);
            // 
            // button14
            // 
            this.button14.Location = new System.Drawing.Point(79, 82);
            this.button14.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button14.Name = "button14";
            this.button14.Size = new System.Drawing.Size(64, 24);
            this.button14.TabIndex = 22;
            this.button14.Text = "小臂(上)";
            this.button14.UseVisualStyleBackColor = true;
            this.button14.Click += new System.EventHandler(this.button14_Click);
            // 
            // button15
            // 
            this.button15.Location = new System.Drawing.Point(78, 136);
            this.button15.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button15.Name = "button15";
            this.button15.Size = new System.Drawing.Size(62, 27);
            this.button15.TabIndex = 23;
            this.button15.Text = "手爪(张)";
            this.button15.UseVisualStyleBackColor = true;
            this.button15.Click += new System.EventHandler(this.button15_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.textBox5);
            this.groupBox2.Controls.Add(this.textBox4);
            this.groupBox2.Controls.Add(this.textBox3);
            this.groupBox2.Controls.Add(this.textBox2);
            this.groupBox2.Controls.Add(this.textBox1);
            this.groupBox2.Controls.Add(this.button15);
            this.groupBox2.Controls.Add(this.button3);
            this.groupBox2.Controls.Add(this.button4);
            this.groupBox2.Controls.Add(this.button5);
            this.groupBox2.Controls.Add(this.button7);
            this.groupBox2.Controls.Add(this.button6);
            this.groupBox2.Controls.Add(this.button14);
            this.groupBox2.Controls.Add(this.button12);
            this.groupBox2.Controls.Add(this.button10);
            this.groupBox2.Controls.Add(this.button11);
            this.groupBox2.Location = new System.Drawing.Point(12, 229);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox2.Size = new System.Drawing.Size(219, 202);
            this.groupBox2.TabIndex = 28;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "控制";
            // 
            // textBox5
            // 
            this.textBox5.Location = new System.Drawing.Point(6, 140);
            this.textBox5.Name = "textBox5";
            this.textBox5.Size = new System.Drawing.Size(67, 21);
            this.textBox5.TabIndex = 28;
            // 
            // textBox4
            // 
            this.textBox4.Location = new System.Drawing.Point(6, 112);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(66, 21);
            this.textBox4.TabIndex = 27;
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(6, 85);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(66, 21);
            this.textBox3.TabIndex = 26;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(6, 58);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(66, 21);
            this.textBox2.TabIndex = 25;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(6, 31);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(66, 21);
            this.textBox1.TabIndex = 24;
            // 
            // pictureBox3
            // 
            this.pictureBox3.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox3.Image")));
            this.pictureBox3.Location = new System.Drawing.Point(245, 12);
            this.pictureBox3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(233, 50);
            this.pictureBox3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox3.TabIndex = 30;
            this.pictureBox3.TabStop = false;
            // 
            // pictureBox4
            // 
            this.pictureBox4.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox4.Image")));
            this.pictureBox4.Location = new System.Drawing.Point(483, 12);
            this.pictureBox4.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pictureBox4.Name = "pictureBox4";
            this.pictureBox4.Size = new System.Drawing.Size(219, 50);
            this.pictureBox4.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox4.TabIndex = 31;
            this.pictureBox4.TabStop = false;
            // 
            // toolStripStatusLabel2
            // 
            this.toolStripStatusLabel2.Name = "toolStripStatusLabel2";
            this.toolStripStatusLabel2.Size = new System.Drawing.Size(64, 17);
            this.toolStripStatusLabel2.Text = "baudRate";
            // 
            // toolStripStatusLabel3
            // 
            this.toolStripStatusLabel3.Name = "toolStripStatusLabel3";
            this.toolStripStatusLabel3.Size = new System.Drawing.Size(34, 17);
            this.toolStripStatusLabel3.Text = "stop";
            // 
            // toolStripStatusLabel4
            // 
            this.toolStripStatusLabel4.Name = "toolStripStatusLabel4";
            this.toolStripStatusLabel4.Size = new System.Drawing.Size(34, 17);
            this.toolStripStatusLabel4.Text = "data";
            // 
            // toolStripStatusLabel5
            // 
            this.toolStripStatusLabel5.Name = "toolStripStatusLabel5";
            this.toolStripStatusLabel5.Size = new System.Drawing.Size(41, 17);
            this.toolStripStatusLabel5.Text = "check";
            // 
            // toolStripStatusLabel6
            // 
            this.toolStripStatusLabel6.Name = "toolStripStatusLabel6";
            this.toolStripStatusLabel6.Size = new System.Drawing.Size(33, 17);
            this.toolStripStatusLabel6.Text = "time";
            // 
            // toolStripStatusLabel7
            // 
            this.toolStripStatusLabel7.Name = "toolStripStatusLabel7";
            this.toolStripStatusLabel7.Size = new System.Drawing.Size(21, 17);
            this.toolStripStatusLabel7.Text = "Tx";
            // 
            // toolStripStatusLabel8
            // 
            this.toolStripStatusLabel8.Name = "toolStripStatusLabel8";
            this.toolStripStatusLabel8.Size = new System.Drawing.Size(22, 17);
            this.toolStripStatusLabel8.Text = "Rx";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel9,
            this.toolStripStatusLabel2,
            this.toolStripStatusLabel3,
            this.toolStripStatusLabel4,
            this.toolStripStatusLabel5,
            this.toolStripStatusLabel6,
            this.toolStripStatusLabel7,
            this.toolStripStatusLabel8});
            this.statusStrip1.Location = new System.Drawing.Point(0, 488);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Padding = new System.Windows.Forms.Padding(1, 0, 15, 0);
            this.statusStrip1.Size = new System.Drawing.Size(714, 22);
            this.statusStrip1.TabIndex = 29;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel9
            // 
            this.toolStripStatusLabel9.Name = "toolStripStatusLabel9";
            this.toolStripStatusLabel9.Size = new System.Drawing.Size(38, 17);
            this.toolStripStatusLabel9.Text = "COM";
            // 
            // timer_now
            // 
            this.timer_now.Enabled = true;
            this.timer_now.Interval = 1000;
            this.timer_now.Tick += new System.EventHandler(this.timer_now_Tick);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(714, 510);
            this.Controls.Add(this.pictureBox4);
            this.Controls.Add(this.pictureBox3);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label_QRCode);
            this.Controls.Add(this.textBoxMsg1);
            this.Controls.Add(this.pictureBox2);
            this.Controls.Add(this.pictureBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.KeyPreview = true;
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.Text = "二维码识别搬动机器人";
            this.Load += new System.EventHandler(this.MainForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).EndInit();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.Button button_camera;
        private System.Windows.Forms.TextBox textBoxMsg1;
        private System.Windows.Forms.Label label_QRCode;
        private System.Windows.Forms.Button button_start;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label_boad;
        private System.Windows.Forms.Label label_com;
        private System.Windows.Forms.ComboBox comboBox_com;
        private System.Windows.Forms.Label label_camera;
        private System.Windows.Forms.Button button_search;
        private System.Windows.Forms.ComboBox comboBox3;
        private System.Windows.Forms.ComboBox comboBox_bort;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button10;
        private System.Windows.Forms.Button button11;
        private System.Windows.Forms.Button button12;
        private System.Windows.Forms.Button button14;
        private System.Windows.Forms.Button button15;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.Label label_check;
        private System.Windows.Forms.Label label_data;
        private System.Windows.Forms.ComboBox comboBox_check;
        private System.Windows.Forms.ComboBox comboBox_data;
        private System.Windows.Forms.ComboBox comboBox_stop;
        private System.Windows.Forms.Label label_stop;
        private System.Windows.Forms.PictureBox pictureBox3;
        private System.Windows.Forms.PictureBox pictureBox4;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel8;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel7;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel6;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel5;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel4;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel3;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel2;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel9;
        private System.Windows.Forms.Timer timer_now;
        private System.Windows.Forms.TextBox textBox5;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox1;
    }
}

