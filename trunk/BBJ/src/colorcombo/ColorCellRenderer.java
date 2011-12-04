

package colorcombo;

import javax.swing.*;
import java.awt.*;

/* Cell renderer class */
public class ColorCellRenderer extends javax.swing.JLabel
        implements javax.swing.ListCellRenderer {

    private Color mCurrentColor;
    boolean mIsChecked;
    
    public ColorCellRenderer() {
         setOpaque(true);
     }
    
    @Override
    public Component getListCellRendererComponent(JList list,
                                                   Object value,
                                                   int index,
                                                   boolean isSelected,
                                                   boolean cellHasFocus) {

         String _r,_g,_b;
         _r = String.valueOf(((Color)value).getRed());
         _g = String.valueOf(((Color)value).getGreen());
         _b = String.valueOf(((Color)value).getBlue());
      
         setText(String.format("R{%s}, G{%s}, B{%s}", new Object[]{_r,_g,_b}));
         mCurrentColor = (Color)value;
         
         Color background;
         Color foreground;

         background = Color.WHITE;
         foreground = Color.WHITE;
        
         background = (Color)list.getModel().getElementAt(index);
         foreground = (Color)list.getModel().getElementAt(index);
     
         try{
             setBackground(background);
             setForeground(foreground);
         }catch (NullPointerException ex){
             
         }

         if (isSelected) {
               mIsChecked = true;
         }else{
               mIsChecked = false;
         }
         return this;
    }

@Override
public void paintComponent(Graphics g) {

    int height = this.getHeight();
    int width = this.getWidth();
  
    super.paintComponent(g);
    g.setColor(Color.WHITE);
    g.fillRect(0, 0, width, height);
 
    g.setColor(Color.BLACK);
    g.drawRect(0, 0, width, height);
  
    g.setColor(mCurrentColor);
    if (mIsChecked == true){
    
        g.fillRect(0, 0, width, height);

        g.fillRect(
          height / 5 ,
          height / 5 ,
          10*3,
          10 );
        g.setColor(Color.BLACK);
        g.drawRect(
          height / 5 - 1,
          height / 5 - 1 ,
          10*3+1,
          11);
    }else{

        g.fillRect(
          height / 5 ,
          height / 5 ,
          10,
          10);
        g.setColor(Color.BLACK);
        g.drawRect(
          height / 5 - 1,
          height / 5 - 1 ,
          11,
          11);
    
    }
}

    @Override
    public void paintChildren(Graphics g){
        super.paintChildren(g);
    }


}


