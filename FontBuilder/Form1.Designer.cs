namespace FontBuilder {
   partial class Form1 {
      /// <summary>
      /// Required designer variable.
      /// </summary>
      private System.ComponentModel.IContainer components = null;

      /// <summary>
      /// Clean up any resources being used.
      /// </summary>
      /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
      protected override void Dispose(bool disposing) {
         if (disposing && (components != null)) {
            components.Dispose();
         }
         base.Dispose(disposing);
      }

      #region Windows Form Designer generated code

      /// <summary>
      /// Required method for Designer support - do not modify
      /// the contents of this method with the code editor.
      /// </summary>
      private void InitializeComponent() {
         this.pictureBox1 = new System.Windows.Forms.PictureBox();
         this.menuStrip1 = new System.Windows.Forms.MenuStrip();
         this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.minCharToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.toolStripTextBox1 = new System.Windows.Forms.ToolStripTextBox();
         this.maxCharToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.toolStripTextBox2 = new System.Windows.Forms.ToolStripTextBox();
         this.zoomToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.toolStripComboBox1 = new System.Windows.Forms.ToolStripComboBox();
         this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
         this.fontDialog1 = new System.Windows.Forms.FontDialog();
         ((System.ComponentModel.ISupportInitialize) (this.pictureBox1)).BeginInit();
         this.menuStrip1.SuspendLayout();
         this.SuspendLayout();
         // 
         // pictureBox1
         // 
         this.pictureBox1.Anchor = ((System.Windows.Forms.AnchorStyles) ((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                     | System.Windows.Forms.AnchorStyles.Left)
                     | System.Windows.Forms.AnchorStyles.Right)));
         this.pictureBox1.BackColor = System.Drawing.Color.Navy;
         this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
         this.pictureBox1.Cursor = System.Windows.Forms.Cursors.Cross;
         this.pictureBox1.Location = new System.Drawing.Point(0, 27);
         this.pictureBox1.Name = "pictureBox1";
         this.pictureBox1.Size = new System.Drawing.Size(522, 155);
         this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
         this.pictureBox1.TabIndex = 0;
         this.pictureBox1.TabStop = false;
         this.pictureBox1.Paint += new System.Windows.Forms.PaintEventHandler(this.pictureBox1_Paint);
         this.pictureBox1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseUp);
         // 
         // menuStrip1
         // 
         this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.minCharToolStripMenuItem,
            this.maxCharToolStripMenuItem,
            this.zoomToolStripMenuItem});
         this.menuStrip1.Location = new System.Drawing.Point(0, 0);
         this.menuStrip1.Name = "menuStrip1";
         this.menuStrip1.Size = new System.Drawing.Size(522, 24);
         this.menuStrip1.TabIndex = 1;
         this.menuStrip1.Text = "menuStrip1";
         // 
         // fileToolStripMenuItem
         // 
         this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.exitToolStripMenuItem});
         this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
         this.fileToolStripMenuItem.Size = new System.Drawing.Size(35, 20);
         this.fileToolStripMenuItem.Text = "&File";
         // 
         // openToolStripMenuItem
         // 
         this.openToolStripMenuItem.Name = "openToolStripMenuItem";
         this.openToolStripMenuItem.Size = new System.Drawing.Size(134, 22);
         this.openToolStripMenuItem.Text = "&Load Font...";
         this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
         // 
         // saveToolStripMenuItem
         // 
         this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
         this.saveToolStripMenuItem.Size = new System.Drawing.Size(134, 22);
         this.saveToolStripMenuItem.Text = "&Save";
         this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
         // 
         // exitToolStripMenuItem
         // 
         this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
         this.exitToolStripMenuItem.Size = new System.Drawing.Size(134, 22);
         this.exitToolStripMenuItem.Text = "E&xit";
         this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
         // 
         // minCharToolStripMenuItem
         // 
         this.minCharToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripTextBox1});
         this.minCharToolStripMenuItem.Name = "minCharToolStripMenuItem";
         this.minCharToolStripMenuItem.Size = new System.Drawing.Size(79, 20);
         this.minCharToolStripMenuItem.Text = "Min Char: 33";
         // 
         // toolStripTextBox1
         // 
         this.toolStripTextBox1.Name = "toolStripTextBox1";
         this.toolStripTextBox1.Size = new System.Drawing.Size(100, 20);
         this.toolStripTextBox1.Text = "33";
         this.toolStripTextBox1.TextChanged += new System.EventHandler(this.toolStripTextBox1_TextChanged);
         // 
         // maxCharToolStripMenuItem
         // 
         this.maxCharToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripTextBox2});
         this.maxCharToolStripMenuItem.Name = "maxCharToolStripMenuItem";
         this.maxCharToolStripMenuItem.Size = new System.Drawing.Size(88, 20);
         this.maxCharToolStripMenuItem.Text = "Max Char: 122";
         // 
         // toolStripTextBox2
         // 
         this.toolStripTextBox2.Name = "toolStripTextBox2";
         this.toolStripTextBox2.Size = new System.Drawing.Size(100, 20);
         this.toolStripTextBox2.Text = "122";
         this.toolStripTextBox2.TextChanged += new System.EventHandler(this.toolStripTextBox2_TextChanged);
         // 
         // zoomToolStripMenuItem
         // 
         this.zoomToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripComboBox1});
         this.zoomToolStripMenuItem.Name = "zoomToolStripMenuItem";
         this.zoomToolStripMenuItem.Size = new System.Drawing.Size(49, 20);
         this.zoomToolStripMenuItem.Text = "Zoom:";
         // 
         // toolStripComboBox1
         // 
         this.toolStripComboBox1.Items.AddRange(new object[] {
            "1x",
            "2x",
            "3x",
            "4x",
            "5x",
            "6x",
            "7x"});
         this.toolStripComboBox1.Name = "toolStripComboBox1";
         this.toolStripComboBox1.Size = new System.Drawing.Size(121, 21);
         this.toolStripComboBox1.SelectedIndexChanged += new System.EventHandler(this.toolStripComboBox1_SelectedIndexChanged);
         // 
         // Form1
         // 
         this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
         this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
         this.ClientSize = new System.Drawing.Size(522, 182);
         this.Controls.Add(this.pictureBox1);
         this.Controls.Add(this.menuStrip1);
         this.MainMenuStrip = this.menuStrip1;
         this.Name = "Form1";
         this.Text = "FontBuilder";
         ((System.ComponentModel.ISupportInitialize) (this.pictureBox1)).EndInit();
         this.menuStrip1.ResumeLayout(false);
         this.menuStrip1.PerformLayout();
         this.ResumeLayout(false);
         this.PerformLayout();

      }

      #endregion

      private System.Windows.Forms.PictureBox pictureBox1;
      private System.Windows.Forms.MenuStrip menuStrip1;
      private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
      private System.Windows.Forms.SaveFileDialog saveFileDialog1;
      private System.Windows.Forms.ToolStripMenuItem minCharToolStripMenuItem;
      private System.Windows.Forms.ToolStripTextBox toolStripTextBox1;
      private System.Windows.Forms.ToolStripMenuItem maxCharToolStripMenuItem;
      private System.Windows.Forms.ToolStripTextBox toolStripTextBox2;
      private System.Windows.Forms.ToolStripMenuItem zoomToolStripMenuItem;
      private System.Windows.Forms.ToolStripComboBox toolStripComboBox1;
      private System.Windows.Forms.FontDialog fontDialog1;
   }
}

