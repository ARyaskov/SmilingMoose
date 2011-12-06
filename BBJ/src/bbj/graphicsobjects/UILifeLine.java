
package bbj.graphicsobjects;

import bbj.graphicsobjects.*;
import bbj.virtualobjects.*;

import java.awt.*;
import javax.swing.*;
/**
 *
 * @author Lemon
 */
public class UILifeLine extends SceneItem{
    
    public UILifeLine(){
        
    }
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        GradientPaint gp = new GradientPaint(0, 0, Color.YELLOW,
                                       0, 10, Color.WHITE);
        Graphics2D g2 = (Graphics2D)g;
        g2.setPaint(gp);
        g2.fillRect(0, 0, 80, 30);       
    }
}
