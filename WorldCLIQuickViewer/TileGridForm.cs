using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WorldCLIQuickViewer
{
    public partial class TileGridForm : Form
    {   
        // Activate Panning https://stackoverflow.com/questions/8985586/a-simple-panning-picturebox-winforms
        // Another idea for it https://social.msdn.microsoft.com/Forums/vstudio/en-US/5823e285-6999-40f5-b28a-74480a0acb13/proper-way-to-zoom-and-pan-images?forum=csharpgeneral
        //  Will eventually need this.
        const int size = 20;
        const int bourder = 5;
        const int offset = 100;
        const int w = 15;
        const int h = 15;
        Tile displayTile
        {
            set
            {
                label_x.Text = value.x.ToString();
                label_y.Text = value.y.ToString();
            }
        }
        Tile[][] matrix;

        public class Tile
        {
            public int x, y;
            public Color c;
            public Tile(int r, int c, Color color)
            {
                x = r;
                y = c;
                this.c = color;
            }
        }

        public class TileBox : PictureBox
        {
            public Tile tile;
            public TileBox(Tile t, EventHandler mouseEnter) : base()
            {
                tile = t;
                base.BackColor = t.c;
                base.Width = size;
                base.Height = size;
                MouseEnter += mouseEnter;
            }
        }


        public TileGridForm()
        {
            this.Hide();
            Random rnd = new Random();
            List<Color> randColor = new List<Color> { Color.Red, Color.Salmon, Color.Green, Color.Orange, Color.Blue, Color.Navy };
            matrix = new Tile[w][];
            for (int i = 0; i < w; i++)
                matrix[i] = new Tile[h];
            for (int c = 0; c < w; c++)
                for (int r = 0; r < h; r++)
                {
                    int index = rnd.Next() % randColor.Count;
                    matrix[r][c] = new Tile(c, r, randColor[index]);
                    TileBox tBox = new TileBox(matrix[r][c], mouse_Enter);
                    tBox.Left = offset + r * (size + bourder);
                    tBox.Top = c * (size + bourder);
                    this.Controls.Add(tBox);
                }
            InitializeComponent();
            displayTile = new Tile(-1, -1, Color.Black);
            this.Show();
        }

        public void mouse_Enter(object sender, EventArgs e)
        {
            if (sender is TileBox)
            {
                TileBox tBox = (TileBox)sender;
                displayTile = tBox.tile;
            }
        }
    }
}
