
package colorcombo;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Vector;

/* Modified class JComboBox */
public final class ColorComboBox extends JComboBox{
    private Color mSelectedColor;
    
    public ColorComboBox()
    {
        super();
        mSelectedColor = Color.WHITE;
        ColorCellRenderer ccrenderer = new ColorCellRenderer();
        this.setRenderer(ccrenderer);
        this.setPreferredSize(new Dimension(60,20));
        this.setMinimumSize(new Dimension(60,20));
    }


    public ColorComboBox(Color[] items) 
    {
        super(items);
        this.setRenderer(new ColorCellRenderer());
        this.setBorder(javax.swing.border.LineBorder.createGrayLineBorder());
        this.setPreferredSize(new Dimension(60,20));
        this.setMinimumSize(new Dimension(60,20));
        this.addItemListener(new ItemListener() {
            @Override
                 public void itemStateChanged(ItemEvent e){
                    mSelectedColor = (Color)e.getItem();    
                 }
               }
        );
        this.setSelectedIndex(0);
    }
    
    public ColorComboBox(Vector items) 
    {
       super(items);
       this.setRenderer(new ColorCellRenderer());
       this.setBorder(javax.swing.border.LineBorder.createGrayLineBorder());
       this.setPreferredSize(new Dimension(60,20));
       this.setMinimumSize(new Dimension(60,20));
       this.addItemListener(new ItemListener() {
            @Override
                 public void itemStateChanged(ItemEvent e){
                    mSelectedColor = (Color)e.getItem();    
                 }
               }
       );
       
       this.setSelectedIndex(0);
    }
    

   @Override
   public void paintComponent(Graphics g) {
  
       super.paintComponent(g);
       g.setColor(Color.WHITE);
       int height = this.getHeight();
       int width = this.getWidth();
       g.fillRect(0, 0, width, height);
       g.setColor(mSelectedColor);
   
       g.fillRect(
          height / 5 ,
          height / 5 ,
          10 * 3,
          10);
       g.setColor(Color.BLACK);
       g.drawRect(
          height / 5 - 1,
          height / 5 - 1 ,
          10 * 3 + 1,
          11);
    

    }

    @Override
    public void paintChildren(Graphics g) {
        super.paintChildren(g);
    }

    @Override
    public void setSelectedIndex(int anIndex) {
        super.setSelectedIndex(anIndex);
        mSelectedColor = (Color)this.getItemAt(anIndex);
    }

    public Color getSelectedColor() {
        return mSelectedColor;
    }
    
    public void setSelectedColor(Color color){
        if (color == null){
            this.setSelectedItem(null);
        }else{
            this.setSelectedItem((Color)color);
            mSelectedColor = color;
        }

    }
  
   
}
