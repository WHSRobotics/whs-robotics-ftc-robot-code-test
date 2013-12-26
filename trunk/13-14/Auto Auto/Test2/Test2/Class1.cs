using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Test2
{
    class FCS
    {
        public Rob rob;
        public bool robCanMove;

        public FCS()
        {
           rob = new Rob();
           robCanMove = false;
        }

        public void moveRob(KeyEventArgs e)
        {
            if (rob.moveEnabled)
            {
                int oldX = rob.x;
                int oldY = rob.y;
                if (e.KeyCode == Keys.Up)// && rob.x >= 264)
                {
                    if (e.KeyCode == Keys.ControlKey && rob.x >= 264)
                        rob.x -= 1;
                    else
                        rob.x -= 5;
                }
                if (e.KeyCode == Keys.Down)// && rob.x <= 409)
                {
                    if (e.KeyCode == Keys.ControlKey && rob.x <= 409)
                        rob.x += 1;
                    else
                        rob.x += 5;
                }
                if (e.KeyCode == Keys.Right)// && rob.y >= -140)
                {
                    if (e.KeyCode == Keys.ControlKey && rob.y >= -140)
                        rob.y -= 1;
                    else
                        rob.y -= 5;
                }
                if (e.KeyCode == Keys.Left)// && rob.y <= 85)
                {
                    if (e.KeyCode == Keys.ControlKey && rob.y <= 85)
                        rob.y += 1;
                    else
                        rob.y += 5;
                }
            }
        }
    }
}
