using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Text;
using System.Windows.Forms;

namespace FontBuilder {
   public partial class Form1 : Form {
      private byte[] map;
      int cur = 1;
      private byte minchar = 33, maxchar = 122;
      private Bitmap pic;
      private Font thefont;
      private Color thecolor;

      public Form1() {
         pic = null;
         map = null;
         InitializeComponent();
         toolStripComboBox1.SelectedIndex = 0;
      }

      private void openToolStripMenuItem_Click(object sender, EventArgs e) {
         fontDialog1.FontMustExist = true;
         fontDialog1.ShowColor = true;
         fontDialog1.ShowEffects = true;
         fontDialog1.ShowDialog(this);

         if (fontDialog1.Font != null) {

            thefont = fontDialog1.Font;
            thecolor = fontDialog1.Color;
            drawfont(thefont, thecolor);

            pictureBox1.Invalidate();
         }

      }

      private void saveToolStripMenuItem_Click(object sender, EventArgs e) {
         saveFileDialog1.AddExtension = true;
         saveFileDialog1.FileName = "";
         saveFileDialog1.Filter = "Font files (*.fnt)|*.fnt";
         saveFileDialog1.ShowDialog();

         if (saveFileDialog1.FileName != "") {
            FileInfo f = new FileInfo(saveFileDialog1.FileName);
            if (!f.Exists) f.Create().Close();
            savefile(saveFileDialog1.FileName, f.Name.Substring(0, f.Name.LastIndexOf('.')) + ".png");
         }
      }

      private void exitToolStripMenuItem_Click(object sender, EventArgs e) {
         Application.Exit();
      }

      private void drawfont(Font f, Color col) {
         int totalwide = 0;

         // render font to bitmap and measure 
         if (minchar >= maxchar || minchar == 0 || maxchar == 0) return;

         pic = new Bitmap(1, 1, System.Drawing.Imaging.PixelFormat.Format32bppArgb);
         Graphics g = Graphics.FromImage(pic);
         g.InterpolationMode = InterpolationMode.NearestNeighbor;
         g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.SingleBitPerPixelGridFit;

         map = new byte[maxchar - minchar + 1];
         for (byte c = minchar; c <= maxchar; c++) {
            map[c- minchar] = (byte) (MeasureDisplayStringWidth(g, "" + (char) c, f));
            totalwide += map[c - minchar];
         }

         pic = new Bitmap(pic, totalwide, f.Height);
         g = Graphics.FromImage(pic);
         g.InterpolationMode = InterpolationMode.NearestNeighbor;
         g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.SingleBitPerPixelGridFit;

         g.FillRectangle(new SolidBrush(Color.FromArgb(255, 255, 0, 255)), 0, 0, totalwide, f.Height);
         
         int curx = -5;
         for (int i = 0; i < map.Length; i++)  {
            g.DrawString("" + ((char) ((byte) (i + minchar))), f, new SolidBrush(col), curx, -1);
            curx += (int) map[i];
         }

      }

      private int MeasureDisplayStringWidth(Graphics graphics, string text, Font font) {

         System.Drawing.StringFormat format = new System.Drawing.StringFormat();
         System.Drawing.RectangleF rect = new System.Drawing.RectangleF(0, 0,
                                                                       1000, 1000);
         System.Drawing.CharacterRange[] ranges = 
                                       { new System.Drawing.CharacterRange(0, 
                                                               text.Length) };
         System.Drawing.Region[] regions = new System.Drawing.Region[1];

         format.SetMeasurableCharacterRanges(ranges);

         regions = graphics.MeasureCharacterRanges(text, font, rect, format);
         rect = regions[0].GetBounds(graphics);

         return (int) (rect.Width);
      }

      private void savefile(string fontfile, string picfile) {
         if (minchar >= maxchar)
            return;

         StreamWriter s = new StreamWriter(fontfile);
         s.WriteLine(picfile);
         s.Write((char) minchar);
         s.Write(' ');
         s.WriteLine((char) maxchar);

         for (int i = 0; i < map.Length; i++) {
            s.Write((char) map[i]);
         }
         s.Close();

         FileInfo f = new FileInfo(fontfile);
         pic.Save(f.DirectoryName + "\\" + picfile);

      }

      private void toolStripTextBox2_TextChanged(object sender, EventArgs e) {
         try {
            maxchar = Byte.Parse(toolStripTextBox2.Text);
            maxCharToolStripMenuItem.Text = "Max Char: " + maxchar.ToString();
            drawfont(thefont, thecolor);
         } catch (Exception x) {
            MessageBox.Show(x.ToString());
            toolStripTextBox2.Text = "0";
         }
      }

      private void toolStripTextBox1_TextChanged(object sender, EventArgs e) {
         try  {
            minchar = Byte.Parse(toolStripTextBox1.Text);
            minCharToolStripMenuItem.Text = "Min Char: " + minchar.ToString();
            drawfont(thefont, thecolor);
         } catch (Exception x) {
            MessageBox.Show(x.ToString());
            toolStripTextBox1.Text = "0";
         }
      }

      private void pictureBox1_Paint(object sender, PaintEventArgs e) {
         if (pic != null) {
            e.Graphics.InterpolationMode = InterpolationMode.NearestNeighbor;
            e.Graphics.DrawImage(pic, 0, 0, cur * pic.Width, cur * pic.Height);

            int curx = (int) map[0];
            for (int i = minchar + 1; i <= maxchar; i++) {
               e.Graphics.DrawLine(new Pen(Color.White), curx * cur, 0, curx * cur, pictureBox1.Height);
               curx += (int) map[i - minchar];
            }
         }
      }

      private void toolStripComboBox1_SelectedIndexChanged(object sender, EventArgs e) {
         cur = Int32.Parse(((string)toolStripComboBox1.SelectedItem).Substring(0, 1));
         zoomToolStripMenuItem.Text = "Zoom: " + ((string)toolStripComboBox1.SelectedItem);
         pictureBox1.Invalidate();
      }

      private void pictureBox1_MouseUp(object sender, MouseEventArgs e) {
      }

   }
}