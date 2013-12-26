using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing.Drawing2D;
using System.Drawing;
using System.Windows.Forms;

namespace Test2
{
    public class Rob : System.Windows.Forms.Label
    {
        private Point topLeft;
        private Point topRight;
        private Point bottomLeft;
        private Point bottomRight;
        private int width;
        private Rectangle r;
        private System.Drawing.Brush myBrush;
        public int x;
        public int y;
        public bool moveEnabled;
        public int angle;
        public String text;
        private Font font;
		

        public Rob()
        {
            x = 150;
            y = 165;
            width = 36;
            moveEnabled = false;
            topLeft = new Point(x, y);
            topRight = new Point(x, y+width);
            bottomLeft = new Point(x+width, y);
            bottomRight = new Point(x+width, y+width);
            angle = 0;
            text = "R";
            r = new Rectangle(x, y, width, width);
            myBrush = new SolidBrush(System.Drawing.Color.Green);
            font = new Font(new FontFamily("Consolas"),20,FontStyle.Bold);
        }

		public void setAngle(int newAngle)
        {
            angle = newAngle;
        }

       public void paint(PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            //g.RotateTransform(45);
 
            Brush b = new SolidBrush(Color.Black);
            g.TranslateTransform(x,y); //middle
            g.RotateTransform(angle);
			g.FillRectangle(myBrush, r);
            g.DrawString(text, font, b,x,y);
            //base.OnPaint(e);
        }

		public void resetPos(int newX, int newY)
        {
            x = newX;
            y = newY;
            topLeft = new Point(x, y);
            topRight = new Point(x, y + width);
            bottomLeft = new Point(x + width, y);
            bottomRight = new Point(x + width, y + width);
            r = new Rectangle(x, y, width, width);
        }

		public String getPosText()
        {
            String pos = "";
            pos += "topLeft: " + topLeft.ToString() +"\n";
            pos += "topRight: " + topRight.ToString() + "\n";
            pos += "bottomLeft: " + bottomLeft.ToString() + "\n";
            pos += "bottomRight: " + bottomRight.ToString() + "\n";
            return pos;
         }

    }
}