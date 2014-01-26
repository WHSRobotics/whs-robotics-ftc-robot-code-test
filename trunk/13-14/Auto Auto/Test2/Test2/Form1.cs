using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
//using System.Windows.Media;

//using Rob;

namespace Test2
{
    public partial class mainForm : Form
    {
        Field field = new Field();
        bool needStart;
        
        public mainForm()
        {
            InitializeComponent();
            needStart = true;
        }

        //private void DrawRob(PaintEventArgs e)
        //{
        //    Brush myBrush = new SolidBrush(Color.Green);
        //    Graphics g = e.Graphics;
        //    g.RotateTransform(45);
        //    g.FillRectangle(myBrush, 150, 50, 36, 36);
        //}
        

        private void mainForm_Paint(object sender, PaintEventArgs e)
        {
            rob1.Location = new Point((int)rob1.x, (int)rob1.y);
            field.paint(e);
            sudoText.paint(rob1.allPtArr,e);
            //rob1.paint(e);
            //DrawRob(e);
        }

        private void mainForm_Load(object sender, EventArgs e)
        {
            transBox.BackColor = System.Drawing.Color.Transparent;
            rob1.BackColor = System.Drawing.Color.Transparent;
            rob1.Image = new Bitmap(@"C:\Users\Proud\whs-robotics-ftc-code-test\13-14\Auto Auto\Test2\Test2\Rob\rob0.gif", true);
        }

        private void mainForm_MouseMove(object sender, MouseEventArgs e)
        {
            
        }

        private void clearBtn_Click(object sender, EventArgs e)
        {
            for (int i = sudoText.Items.Count; i > 0; i--)
                sudoText.removeAct();
            needStart = true;
            UpdateBtn.Enabled = false;
            startBtn.Enabled = true;
            dtPowText.Enabled = false;
            rob1.clear();
            //rob1.resetPos(200,225);
            //Refresh();
        }

        private PointF getNextPt(PointF pt, String dir, int inc)
        {
            PointF nextPt = pt;

            if (dir == "x")
                nextPt.X += inc;
            else if (dir == "y")
                nextPt.Y += inc;

            return nextPt;
        }

        private bool robInField(String dir, int inc)
        {
            PointF nextPt;
            bool check = true;

            for (int i = 0; i < 4; i++)
            {
                if (check == true)
                {
                    nextPt = getNextPt(rob1.ptArr[i], dir, inc);
                    check = field.checkPoint(nextPt);
                    Console.WriteLine(i + ": " + check);
                }
            }

            return check;
        }


        private void mainForm_KeyDown(object sender, KeyEventArgs e)
        {
            //myFCS.moveRob(e);
            if (rob1.moveEnabled)
            {
                if (e.KeyCode == Keys.Left && robInField("x", -5)) // && rob1.x >= FIELD_TOPX+5)
                {
                    if (e.Modifiers != Keys.Alt)
                    {
                        rob1.moveStraight("x", -5);
                    }
                    else if(robInField("x", -1))
                    {
                        rob1.moveStraight("x", -1);
                    }
                     
                }
                if (e.KeyCode == Keys.Right && robInField("x", 5))// && rob1.x <= FIELD_BOTTOMX-5)
                {
                    if (e.Modifiers != Keys.Alt)// && rob1.x <= FIELD_BOTTOMX - 1)
                        rob1.moveStraight("x", 5);
                    else if (robInField("x", 1))
                    {
                        rob1.moveStraight("x", 1);
                    }
                }
                if (e.KeyCode == Keys.Up && robInField("y", -5))// && rob1.y >= FIELD_RIGHTY+5)
                {
                    if (e.Modifiers != Keys.Alt)// && rob1.y >= FIELD_RIGHTY + 1)
                        rob1.moveStraight("y", -5);
                    else if (robInField("y", -1))
                    {
                        rob1.moveStraight("y", -1);
                    }
                       
                }
                if (e.KeyCode == Keys.Down && robInField("y", 5))// && rob1.y <= FIELD_LEFTY-5)
                {
                    if (e.Modifiers != Keys.Alt) //&& rob1.y <= FIELD_LEFTY - 1)
                        rob1.moveStraight("y", 5);
                    else if (robInField("y", 1))
                    {
                        rob1.moveStraight("y", 1);
                    }
                }
                if(e.KeyCode == Keys.S)
                {
                    rob1.rotate(5);
                }
                if(e.KeyCode == Keys.A)
                {
                    rob1.rotate(-5);
                }
                if(e.KeyCode == Keys.U && !needStart)
                {
                    UpdateBtn.Enabled = true;
                        UpdateBtn.PerformClick();
                        UpdateBtn.Enabled = false;
                }
            }
            rob1.resetPos(rob1.x, rob1.y);
            //rob1.Location = new Point(rob1.x,rob1.y);
            Refresh();
            robCoordLbl.Text = rob1.getPosText();//rob1.vector.getText();//getPosText();
        }

        private void transBox_Paint(object sender, PaintEventArgs e)
        {
            rob1.Location = new Point((int)rob1.x, (int)rob1.y);
            //rob1.paint(e);
        }

        private void transBox_MouseEnter(object sender, EventArgs e)
        {
            rob1.moveEnabled = true;
            /*drawRadio.Enabled = false;
            turnRadio.Enabled = false;
            eraseRadio.Enabled = false;*/
            UpdateBtn.Enabled = false;
            sudoText.Enabled = false;
            exportBtn.Enabled = false;
            clearBtn.Enabled = false;
            startBtn.Enabled = false;
            dtPowText.Enabled = false;
        }

        private void transBox_MouseLeave(object sender, EventArgs e)
        {
            rob1.moveEnabled = false;
            /*drawRadio.Enabled = true;
            turnRadio.Enabled = true;
            eraseRadio.Enabled = true;*/
            if (needStart)
            {
                UpdateBtn.Enabled = false;
                startBtn.Enabled = true;
                dtPowText.Enabled = false;
            }
            else
            {
                UpdateBtn.Enabled = true;
                startBtn.Enabled = false;
                dtPowText.Enabled = true;
            }
            sudoText.Enabled = true;
            exportBtn.Enabled = true;
            clearBtn.Enabled = true;
          
        }

        private void UpdateBtn_Click(object sender, EventArgs e)
        {
            int index = -1;
            if (sudoText.SelectedIndices.Count == 1)
            {
                index = sudoText.SelectedIndex+1;
            }//Items.RemoveAt(SelectedIndex);
            else if (sudoText.SelectedIndices.Count == 0)
            {
                index = sudoText.Items.Count;
            }
                //Items.RemoveAt(Items.Count - 1);
 
            else if (sudoText.SelectedIndices.Count > 1)
            {
                index = sudoText.SelectedIndices[sudoText.SelectedIndices.Count - 1]; //last index selected   
            }

            float pow = float.Parse(dtPowText.Text);
            rob1.setArrs(index);
            sudoText.addAct(index, rob1.getArrVal("d", index), rob1.getArrVal("ang",index), pow);

            sudoText.TopIndex = sudoText.Items.Count - 1; //auto scroll to bottom
        }

        private void sudoText_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Back && sudoText.SelectedIndices.Count > 0)
            {
                sudoText.removeAct();
            }
        }

        private void startBtn_Click(object sender, EventArgs e)
        {
            sudoText.addStart(rob1.x, rob1.y, rob1.realAngle);
            rob1.clear();
            needStart = false;
            startBtn.Enabled = false;
            UpdateBtn.Enabled = true;
            dtPowText.Enabled = true;
        }


        private void dtPowText_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Enter)
            {
                float num;
                bool isNum = float.TryParse(dtPowText.Text, out num);
                if(isNum)
                {
                    if(num < 0)
                    {
                        dtPowText.Text = "0";
                    }
                    else if(num > 100)
                    {
                        dtPowText.Text = "100";
                    }
                }
                else
                {
                    dtPowText.Text = "0";
                }
            }
        }

        private void exportBtn_Click(object sender, EventArgs e)
        {
            String code = sudoText.convertCode();
            var result = MessageBox.Show(code, "Your Code", MessageBoxButtons.OKCancel);
            if (result == DialogResult.OK)
            {
                Clipboard.SetText(code);
                MessageBox.Show("Code copied to clipboard!");
            }
        }


    }
}
