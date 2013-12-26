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
            this.drawRadio = new System.Windows.Forms.RadioButton();
            this.turnRadio = new System.Windows.Forms.RadioButton();
            this.eraseRadio = new System.Windows.Forms.RadioButton();
            this.UpdateBtn = new System.Windows.Forms.Button();
            this.sudoText = new System.Windows.Forms.TextBox();
            this.sudoLbl = new System.Windows.Forms.Label();
            this.exportBtn = new System.Windows.Forms.Button();
            this.clearBtn = new System.Windows.Forms.Button();
            this.instructLbl = new System.Windows.Forms.Label();
            this.robCoordLbl = new System.Windows.Forms.Label();
            this.transBox = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.transBox)).BeginInit();
            this.SuspendLayout();
            // 
            // drawRadio
            // 
            this.drawRadio.AutoSize = true;
            this.drawRadio.Enabled = false;
            this.drawRadio.Location = new System.Drawing.Point(579, 10);
            this.drawRadio.Name = "drawRadio";
            this.drawRadio.Size = new System.Drawing.Size(73, 17);
            this.drawRadio.TabIndex = 0;
            this.drawRadio.TabStop = true;
            this.drawRadio.Text = "Draw Line";
            this.drawRadio.UseVisualStyleBackColor = true;
            // 
            // turnRadio
            // 
            this.turnRadio.AutoSize = true;
            this.turnRadio.Enabled = false;
            this.turnRadio.Location = new System.Drawing.Point(578, 34);
            this.turnRadio.Name = "turnRadio";
            this.turnRadio.Size = new System.Drawing.Size(47, 17);
            this.turnRadio.TabIndex = 1;
            this.turnRadio.TabStop = true;
            this.turnRadio.Text = "Turn";
            this.turnRadio.UseVisualStyleBackColor = true;
            // 
            // eraseRadio
            // 
            this.eraseRadio.AutoSize = true;
            this.eraseRadio.Enabled = false;
            this.eraseRadio.Location = new System.Drawing.Point(578, 57);
            this.eraseRadio.Name = "eraseRadio";
            this.eraseRadio.Size = new System.Drawing.Size(85, 17);
            this.eraseRadio.TabIndex = 2;
            this.eraseRadio.TabStop = true;
            this.eraseRadio.Text = "Erase Action";
            this.eraseRadio.UseVisualStyleBackColor = true;
            // 
            // UpdateBtn
            // 
            this.UpdateBtn.Enabled = false;
            this.UpdateBtn.Location = new System.Drawing.Point(609, 131);
            this.UpdateBtn.Name = "UpdateBtn";
            this.UpdateBtn.Size = new System.Drawing.Size(144, 26);
            this.UpdateBtn.TabIndex = 3;
            this.UpdateBtn.Text = "Update Code";
            this.UpdateBtn.UseVisualStyleBackColor = true;
            // 
            // sudoText
            // 
            this.sudoText.Enabled = false;
            this.sudoText.Location = new System.Drawing.Point(578, 192);
            this.sudoText.Multiline = true;
            this.sudoText.Name = "sudoText";
            this.sudoText.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.sudoText.Size = new System.Drawing.Size(214, 280);
            this.sudoText.TabIndex = 4;
            // 
            // sudoLbl
            // 
            this.sudoLbl.AutoSize = true;
            this.sudoLbl.Location = new System.Drawing.Point(572, 172);
            this.sudoLbl.Name = "sudoLbl";
            this.sudoLbl.Size = new System.Drawing.Size(112, 13);
            this.sudoLbl.TabIndex = 5;
            this.sudoLbl.Text = "Program Pseudocode:";
            // 
            // exportBtn
            // 
            this.exportBtn.Enabled = false;
            this.exportBtn.Location = new System.Drawing.Point(575, 489);
            this.exportBtn.Name = "exportBtn";
            this.exportBtn.Size = new System.Drawing.Size(118, 23);
            this.exportBtn.TabIndex = 6;
            this.exportBtn.Text = "Export Code";
            this.exportBtn.UseVisualStyleBackColor = true;
            // 
            // clearBtn
            // 
            this.clearBtn.Enabled = false;
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
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.ClientSize = new System.Drawing.Size(804, 524);
            this.Controls.Add(this.robCoordLbl);
            this.Controls.Add(this.transBox);
            this.Controls.Add(this.instructLbl);
            this.Controls.Add(this.clearBtn);
            this.Controls.Add(this.exportBtn);
            this.Controls.Add(this.sudoLbl);
            this.Controls.Add(this.sudoText);
            this.Controls.Add(this.UpdateBtn);
            this.Controls.Add(this.eraseRadio);
            this.Controls.Add(this.turnRadio);
            this.Controls.Add(this.drawRadio);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "mainForm";
            this.Text = "WHSFTC542 Auto Auto Generator";
            this.Load += new System.EventHandler(this.mainForm_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.mainForm_Paint);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.mainForm_KeyDown);
            ((System.ComponentModel.ISupportInitialize)(this.transBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton drawRadio;
        private System.Windows.Forms.RadioButton turnRadio;
        private System.Windows.Forms.RadioButton eraseRadio;
        private System.Windows.Forms.Button UpdateBtn;
        private System.Windows.Forms.TextBox sudoText;
        private System.Windows.Forms.Label sudoLbl;
        private System.Windows.Forms.Button exportBtn;
        private System.Windows.Forms.Button clearBtn;
        private System.Windows.Forms.Label instructLbl;
        private System.Windows.Forms.Label robCoordLbl;
        private System.Windows.Forms.PictureBox transBox;
        
    }
}

