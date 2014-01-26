using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing.Drawing2D;
using System.Drawing;
using System.Windows.Forms;
using System.Windows.Media;
using System.Collections;

namespace Test2
{
    public class Rob : System.Windows.Forms.PictureBox
    {
        public PointF topLeft;
        public PointF prevTL;
        private PointF topRight;
        private PointF bottomLeft;
        private PointF bottomRight;
        private PointF centre;
        private float width;
        //private Rectangle r;
        private System.Drawing.Brush myBrush;
        public bool moveEnabled;
        public float realAngle;
        public float prevAngle;
        public float picAngle;
        //public String text;
        //private Font font;
        private float hwidth; //half width
        public float xOff;
        public float yOff;
        public float x;
        public float y;
        private float xDiff;
        private float yDiff;
        private float dAmt;
        public RightTriangle vector;
        private PointF triPt;//23
        public PointF[] ptArr = new PointF[4];
        private List<float> dArr = new List<float>();
        private List<float> angArr = new List<float>(); //angle change
        private bool isNeg;
        public List<PointF> allPtArr = new List<PointF>();
        //private ArrayList dArr = new ArrayList();
        //private ArrayList angArr = new ArrayList(); //angle change

        public Rob()
        {
            realAngle = 0;
            topLeft = new PointF((float)200.0,(float)200.0);
            prevTL = topLeft;
            prevAngle = realAngle;
            width = (float)36.0;
            moveEnabled = false;
           /* topLeft = new Point(x, y);
            topRight = new Point(x, y+width);
            bottomLeft = new Point(x+width, y);
            bottomRight = new Point(x+width, y+width);
            realAngle = 0;
            picAngle = 0;*/
            //text = "R";
            //this.BackColor = System.Drawing.Color.Green;
            hwidth = (float)(width / 2.0);


            centre.X = (float)(topLeft.X + hwidth);
            centre.Y = (float)(topLeft.Y + hwidth);

            triPt.X = (float)(topLeft.X);
            triPt.Y = (float)(topLeft.Y);

            vector = new RightTriangle(triPt, realAngle, 5);
             xOff = vector.xSide;
             yOff = vector.ySide;

            x = topLeft.X;
            y = topLeft.Y;

            topRight.X = (float)(centre.X + hwidth);
            topRight.Y = (float)(centre.Y - hwidth);

            bottomLeft.X = (float)(centre.X - hwidth);
            bottomLeft.Y = (float)(centre.Y + hwidth);

            bottomRight.X = (float)(centre.X + hwidth);
            bottomRight.Y = (float)(centre.Y + hwidth);
            //r = new Rectangle(x, y, width, width);
            myBrush = new SolidBrush(System.Drawing.Color.Green);
            //font = new Font(new System.Drawing.FontFamily("Consolas"),20,FontStyle.Bold);

            updateArr();
        }

        private void updateArr()
        {
            ptArr[0] = topLeft;
            ptArr[1] = topRight;
            ptArr[2] = bottomLeft;
            ptArr[3] = bottomRight;
        }

        public void setArrs(int index)
        {
            Console.WriteLine("prevTL = " + prevTL.ToString());
            Console.WriteLine("topLeft = " + topLeft.ToString());
            Console.WriteLine("prevAngle = " + prevAngle);
            Console.WriteLine("realAngle = " + realAngle);

            float angDiff = realAngle - prevAngle;
            Console.WriteLine("angDiff = " + angDiff);
            if (index < angArr.Count)
            {
                angArr[index] = angDiff;
                angArr.Insert(index + 1, angDiff);
            }
            else
            {
                angArr.Add(angDiff);
                angArr.Add(angDiff);
            }
            prevAngle = realAngle;

            xDiff = topLeft.X - prevTL.X;
            yDiff = topLeft.Y - prevTL.Y;
            dAmt = (float)(Math.Sqrt(Math.Pow(xDiff, 2) + Math.Pow(yDiff, 2))); //dist formula
            if(isNeg)
            {
                dAmt = -dAmt;
            }

            if (index < dArr.Count)
            {
                dArr[index] = dAmt;
                dArr.Insert(index + 1, dAmt);
            }
            else
            {
                dArr.Add(dAmt);
                dArr.Add(dAmt);
            }

            prevTL = topLeft;
            allPtArr.Add(topLeft);
            Console.WriteLine("dAmt: " + dAmt);
        }

        public float getArrVal(String type, int index)
        {
            if(type == "d")
            {
                return (float)dArr[index];
            }
            else
            {
                return (float)angArr[index];
            }
        }

        public void deleteFromArr(String arr, int i, int c)
        {
            if(arr == "d")
            {
                dArr.RemoveRange(i, c);
            }
            else if(arr == "ang")
            {
                angArr.RemoveRange(i, c);
            }
        }

        /*
        public void moveTri(String dir, int amt)
        {
            if(dir == "x")
            {
                triPt.X = topLeft.X;
            }
            else if(dir == "y")
            {
                triPt.Y = topLeft.Y;
            }
            vector.updateDimensions(triPt, realAngle, 50);
        }*/

        public void moveStraight(String dir, float distance)
        {
            //triPt.X = (int)(centre.X - hwidth - 8.0 + 25);
            //triPt.Y =(int)(centre.Y - hwidth - 8.0);

            if (dir == "y")
                vector.updateDimensions("y", triPt, realAngle, distance);
            else if (dir == "x")
                vector.updateDimensions("x", triPt, realAngle, distance);
            
             xOff = vector.xSide;
             yOff = vector.ySide;

             isNeg = (distance > 0);

             topLeft.X += xOff;
             topLeft.Y += yOff;
             bottomLeft.X += xOff;
             bottomLeft.Y += yOff;
             topRight.X += xOff;
             topRight.Y += yOff;
             bottomRight.X += xOff;
             bottomRight.Y += yOff;
             x = topLeft.X;
             y = topLeft.Y;

             updateArr();
            /*
            topLeft.X = (int)(centre.X - hwidth + xOff);
            topLeft.Y = (int)(centre.Y - hwidth + yOff);

            x = topLeft.X;
            y = topLeft.Y;

            topRight.X = (int)(centre.X + hwidth + xOff);
            topRight.Y = (int)(centre.Y - hwidth + yOff);

            bottomLeft.X = (int)(centre.X - hwidth + xOff);
            bottomLeft.Y = (int)(centre.Y + hwidth + yOff);

            bottomRight.X = (int)(centre.X + hwidth + xOff);
            bottomRight.Y = (int)(centre.Y + hwidth + yOff);*/
        }

        public void rotate(float amt)
        {
            realAngle += amt;
            updateAngle();
        }

		public void updateAngle()
        {
            if(Math.Abs(realAngle) >= 360)
            {
                realAngle = realAngle % 360;
            }
            if(realAngle < 0)
            {
                picAngle = 360 - Math.Abs(realAngle);
            }
            else
            {
                picAngle = realAngle;
            }
            String fileName = "rob" + picAngle + ".gif";
            this.Image = new Bitmap(@"C:\Users\Proud\whs-robotics-ftc-code-test\13-14\Auto Auto\Test2\Test2\Rob\" + fileName, true);

        }


       public void paint(PaintEventArgs e)
        {
            Graphics g = e.Graphics;
           
            //g.FillPolygon(myBrush, vector.ptArr);
            //g.RotateTransform(45);
 
           // System.Drawing.Brush b = new SolidBrush(System.Drawing.Color.Black);
          /*  g.TranslateTransform(this.Location.X + offset, this.Location.Y + offset);//x,y); //middle
           g.RotateTransform(angle);
            g.TranslateTransform(-this.Location.X - offset, -this.Location.Y - offset);*/
			//g.FillRectangle(myBrush, r);
            //g.DrawString(text, font, b,x,y);
            //base.OnPaint(e);
        }

		public void resetPos(float newX, float newY)
        {
            centre = new PointF(newX + hwidth, newY + hwidth);
            topLeft = new PointF(newX, newY);
            x = newX;
            y = newY;
            
            topRight = new PointF(newX + width, newY);
            bottomLeft = new PointF(newX, newY + width);
            bottomRight = new PointF(newX + width, newY + width);
            //r = new Rectangle(x, y, width, width);
        }

		public String getPosText()
        {
            String pos = "";
            pos += "topLeft: " + topLeft.ToString() +"\n";
            pos += "topRight: " + topRight.ToString() + "\n";
            pos += "bottomLeft: " + bottomLeft.ToString() + "\n";
            pos += "bottomRight: " + bottomRight.ToString() + "\n";
            pos += "picAngle: " + picAngle + "   realAngle: " + realAngle;
            return pos;
         }

        public void clear()
        {
            prevTL = topLeft;
            prevAngle = realAngle;
        }

    }
}