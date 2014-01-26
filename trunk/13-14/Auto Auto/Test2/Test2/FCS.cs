using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Test2
{
    public class FCS
    {
        public Rob rob;
        public bool robCanMove;
        public const int FIELD_TOPX = 255;
        public const int FIELD_BOTTOMX = 500;
        public const int FIELD_LEFTY = 95;
        public const int FIELD_RIGHTY = -150;

        public FCS()
        {
           //rob = new Rob(new Point(50,50));
           rob.Image = new Bitmap(@"C:\Users\Proud\whs-robotics-ftc-code-test\13-14\Auto Auto\Test2\Test2\Rob\rob0.gif", false);
           robCanMove = false;
        }

        public void moveRob(KeyEventArgs e)
        {
            if (rob.moveEnabled)
            {
                int oldX = (int)rob.x;
                int oldY = (int)rob.y;
                if (e.KeyCode == Keys.Left)// && rob.x >= FIELD_TOPX+5)
                {
                    if (e.Modifiers == Keys.Alt && rob.x >= FIELD_TOPX+1)
                        rob.x -= 1;
                    else
                        rob.x -= 5;
                }
                if (e.KeyCode == Keys.Right)// && rob.x <= FIELD_BOTTOMX-5)
                {
                    if (e.Modifiers == Keys.Alt && rob.x <= FIELD_BOTTOMX-1)
                        rob.x += 1;
                    else
                        rob.x += 5;
                }
                if (e.KeyCode == Keys.Up)// && rob.y >= FIELD_RIGHTY+5)
                {
                    if (e.Modifiers == Keys.Alt && rob.y >= FIELD_RIGHTY+1)
                        rob.y -= 1;
                    else
                        rob.y -= 5;
                }
                if (e.KeyCode == Keys.Down)// && rob.y <= FIELD_LEFTY-5)
                {
                    if (e.Modifiers == Keys.Alt && rob.y <= FIELD_LEFTY-1)
                        rob.y += 1;
                    else
                        rob.y += 5;
                }
            }
        }
    }
}
