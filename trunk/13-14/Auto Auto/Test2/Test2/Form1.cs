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
        public const int FIELD_TOPX = 255;
        public const int FIELD_BOTTOMX = 500;
        public const int FIELD_LEFTY = 95;
        public const int FIELD_RIGHTY = -150;
        public Rob myRob = new Rob();
        //public FCS myFCS;

        public mainForm()
        {
            InitializeComponent();
            //myFCS = new FCS();
            //myRob = myFCS.rob;
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
 
            myRob.paint(e);
            //DrawRob(e);
        }

        private void mainForm_Load(object sender, EventArgs e)
        {
            transBox.BackColor = System.Drawing.Color.Transparent;
                  
        }

        private void mainForm_MouseMove(object sender, MouseEventArgs e)
        {
 
        }

        private void clearBtn_Click(object sender, EventArgs e)
        {
            myRob.resetPos(200,225);
            Refresh();
        }

        private void mainForm_KeyDown(object sender, KeyEventArgs e)
        {
            //myFCS.moveRob(e);
            if (myRob.moveEnabled)
            {
                int oldX = myRob.x;
                int oldY = myRob.y;
                if (e.KeyCode == Keys.Left)// && myRob.x >= FIELD_TOPX+5)
                {
                    if (e.Modifiers == Keys.Alt && myRob.x >= FIELD_TOPX + 1)
                        myRob.x -= 1;
                    else
                        myRob.x -= 5;
                }
                if (e.KeyCode == Keys.Right)// && myRob.x <= FIELD_BOTTOMX-5)
                {
                    if (e.Modifiers == Keys.Alt && myRob.x <= FIELD_BOTTOMX - 1)
                        myRob.x += 1;
                    else
                        myRob.x += 5;
                }
                if (e.KeyCode == Keys.Up)// && myRob.y >= FIELD_RIGHTY+5)
                {
                    if (e.Modifiers == Keys.Alt && myRob.y >= FIELD_RIGHTY + 1)
                        myRob.y -= 1;
                    else
                        myRob.y -= 5;
                }
                if (e.KeyCode == Keys.Down)// && myRob.y <= FIELD_LEFTY-5)
                {
                    if (e.Modifiers == Keys.Alt && myRob.y <= FIELD_LEFTY - 1)
                        myRob.y += 1;
                    else
                        myRob.y += 5;
                }
                if(e.KeyCode == Keys.S)
                {
                    myRob.angle += 5;
                }
                if(e.KeyCode == Keys.A)
                {
                    myRob.angle -= 5;
                }
            }
            myRob.resetPos(myRob.x, myRob.y);
            myRob.setAngle(myRob.angle);
            //myRob.Location = new Point(myRob.x,myRob.y);
            Refresh();
            robCoordLbl.Text = myRob.getPosText();
        }

        private void transBox_Paint(object sender, PaintEventArgs e)
        {
            myRob.paint(e);
        }

        private void transBox_MouseEnter(object sender, EventArgs e)
        {
            myRob.moveEnabled = true;
        }

        private void transBox_MouseLeave(object sender, EventArgs e)
        {
            myRob.moveEnabled = false;
        }



    }
}
