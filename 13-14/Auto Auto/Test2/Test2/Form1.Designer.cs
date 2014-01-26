namespace Test2
{
    partial class mainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(mainForm));
            this.UpdateBtn = new System.Windows.Forms.Button();
            this.sudoLbl = new System.Windows.Forms.Label();
            this.exportBtn = new System.Windows.Forms.Button();
            this.clearBtn = new System.Windows.Forms.Button();
            this.instructLbl = new System.Windows.Forms.Label();
            this.robCoordLbl = new System.Windows.Forms.Label();
            this.transBox = new System.Windows.Forms.PictureBox();
            this.startBtn = new System.Windows.Forms.Button();
            this.dtPowText = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.sudoText = new Test2.CodeBox();
            this.rob1 = new Test2.Rob();
            ((System.ComponentModel.ISupportInitialize)(this.transBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.rob1)).BeginInit();
            this.SuspendLayout();
            // 
            // UpdateBtn
            // 
            this.UpdateBtn.Location = new System.Drawing.Point(573, 11);
            this.UpdateBtn.Name = "UpdateBtn";
            this.UpdateBtn.Size = new System.Drawing.Size(144, 26);
            this.UpdateBtn.TabIndex = 3;
            this.UpdateBtn.Text = "Update Code";
            this.UpdateBtn.UseVisualStyleBackColor = true;
            this.UpdateBtn.Click += new System.EventHandler(this.UpdateBtn_Click);
            // 
            // sudoLbl
            // 
            this.sudoLbl.AutoSize = true;
            this.sudoLbl.Location = new System.Drawing.Point(570, 67);
            this.sudoLbl.Name = "sudoLbl";
            this.sudoLbl.Size = new System.Drawing.Size(112, 13);
            this.sudoLbl.TabIndex = 5;
            this.sudoLbl.Text = "Program Pseudocode:";
            // 
            // exportBtn
            // 
            this.exportBtn.Location = new System.Drawing.Point(575, 489);
            this.exportBtn.Name = "exportBtn";
            this.exportBtn.Size = new System.Drawing.Size(118, 23);
            this.exportBtn.TabIndex = 6;
            this.exportBtn.Text = "Export Code";
            this.exportBtn.UseVisualStyleBackColor = true;
            this.exportBtn.Click += new System.EventHandler(this.exportBtn_Click);
            // 
            // clearBtn
            // 
            this.clearBtn.Location = new System.Drawing.Point(699, 487);
            this.clearBtn.Name = "clearBtn";
            this.clearBtn.Size = new System.Drawing.Size(85, 25);
            this.clearBtn.TabIndex = 7;
            this.clearBtn.Text = "Clear All";
            this.clearBtn.UseVisualStyleBackColor = true;
            this.clearBtn.Click += new System.EventHandler(this.clearBtn_Click);
            // 
            // instructLbl
            // 
            this.instructLbl.AutoSize = true;
            this.instructLbl.Location = new System.Drawing.Point(576, 89);
            this.instructLbl.Name = "instructLbl";
            this.instructLbl.Size = new System.Drawing.Size(0, 13);
            this.instructLbl.TabIndex = 8;
            // 
            // robCoordLbl
            // 
            this.robCoordLbl.AutoSize = true;
            this.robCoordLbl.Location = new System.Drawing.Point(0, 450);
            this.robCoordLbl.Name = "robCoordLbl";
            this.robCoordLbl.Size = new System.Drawing.Size(0, 13);
            this.robCoordLbl.TabIndex = 9;
            // 
            // transBox
            // 
            this.transBox.BackColor = System.Drawing.SystemColors.MenuHighlight;
            this.transBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.transBox.Image = ((System.Drawing.Image)(resources.GetObject("transBox.Image")));
            this.transBox.Location = new System.Drawing.Point(0, 0);
            this.transBox.Name = "transBox";
            this.transBox.Size = new System.Drawing.Size(564, 524);
            this.transBox.TabIndex = 10;
            this.transBox.TabStop = false;
            this.transBox.Paint += new System.Windows.Forms.PaintEventHandler(this.transBox_Paint);
            this.transBox.MouseEnter += new System.EventHandler(this.transBox_MouseEnter);
            this.transBox.MouseLeave += new System.EventHandler(this.transBox_MouseLeave);
            // 
            // startBtn
            // 
            this.startBtn.Location = new System.Drawing.Point(717, 12);
            this.startBtn.Name = "startBtn";
            this.startBtn.Size = new System.Drawing.Size(75, 23);
            this.startBtn.TabIndex = 13;
            this.startBtn.Text = "Set Start";
            this.startBtn.UseVisualStyleBackColor = true;
            this.startBtn.Click += new System.EventHandler(this.startBtn_Click);
            // 
            // dtPowText
            // 
            this.dtPowText.Location = new System.Drawing.Point(634, 41);
            this.dtPowText.Name = "dtPowText";
            this.dtPowText.Size = new System.Drawing.Size(49, 20);
            this.dtPowText.TabIndex = 14;
            this.dtPowText.Text = "100";
            this.dtPowText.KeyDown += new System.Windows.Forms.KeyEventHandler(this.dtPowText_KeyDown);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(576, 44);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 13);
            this.label1.TabIndex = 15;
            this.label1.Text = "DT Power";
            // 
            // sudoText
            // 
            this.sudoText.FormattingEnabled = true;
            this.sudoText.HorizontalScrollbar = true;
            this.sudoText.Location = new System.Drawing.Point(575, 83);
            this.sudoText.Name = "sudoText";
            this.sudoText.Size = new System.Drawing.Size(215, 394);
            this.sudoText.TabIndex = 12;
            // 
            // rob1
            // 
            this.rob1.Image = global::Test2.Properties.Resources.rob0;
            this.rob1.Location = new System.Drawing.Point(429, 134);
            this.rob1.Name = "rob1";
            this.rob1.Size = new System.Drawing.Size(51, 53);
            this.rob1.TabIndex = 11;
            this.rob1.TabStop = false;
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.ClientSize = new System.Drawing.Size(804, 524);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.dtPowText);
            this.Controls.Add(this.startBtn);
            this.Controls.Add(this.sudoText);
            this.Controls.Add(this.rob1);
            this.Controls.Add(this.robCoordLbl);
            this.Controls.Add(this.transBox);
            this.Controls.Add(this.instructLbl);
            this.Controls.Add(this.clearBtn);
            this.Controls.Add(this.exportBtn);
            this.Controls.Add(this.sudoLbl);
            this.Controls.Add(this.UpdateBtn);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "mainForm";
            this.Text = "WHSFTC542 Auto Auto Generator";
            this.Load += new System.EventHandler(this.mainForm_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.mainForm_Paint);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.mainForm_KeyDown);
            ((System.ComponentModel.ISupportInitialize)(this.transBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.rob1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button UpdateBtn;
        private System.Windows.Forms.Label sudoLbl;
        private System.Windows.Forms.Button exportBtn;
        private System.Windows.Forms.Button clearBtn;
        private System.Windows.Forms.Label instructLbl;
        private System.Windows.Forms.Label robCoordLbl;
        private System.Windows.Forms.PictureBox transBox;
        private Rob rob1;
        private CodeBox sudoText;
        private System.Windows.Forms.Button startBtn;
        private System.Windows.Forms.TextBox dtPowText;
        private System.Windows.Forms.Label label1;
        
    }
}

