/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Polygon;
import java.awt.Stroke;

/**
 *
 * @author Alexander
 */
public class UIActorLifeLine extends UILifeLine {

    UIActorLifeLine(int x, int y, String text){
        
        fillData(x,y,text);
                
        SceneItemListener listener = new SceneItemListener(this);

        this.addMouseListener(listener);
        this.addMouseMotionListener(listener);
        this.setToolTipText("Исполнитель: " + m_text);
    }
            
    @Override
    public void specificPaint(Graphics g) {
        
        m_textCoordX = x+10;
        m_textCoordY = y+47;
        
        Graphics2D g2 = (Graphics2D)g;
                     
        if (m_isSelected)   // Рисуем границы полигона красным цветом
            g2.setColor(Color.red);
        else                // Рисуем границы полигона черным цветом
            g2.setColor(Color.black);
        
        if (m_isSelected){
            g2.setStroke(new BasicStroke(1));
            Polygon p = new Polygon();          // Полигон комментария

            p.addPoint(x, y);
            p.addPoint(x + 120, y);
            p.addPoint(x + 120, y + 50);
            p.addPoint(x, y + 50);

            g.drawPolygon(p);     
        }

        if (m_isSelected)   // Рисуем границы полигона красным цветом
            g2.setColor(Color.red);
        else                // Рисуем границы полигона черным цветом
            g2.setColor(Color.black);
                
        // Рисуем человечка
        g2.setStroke(new BasicStroke(3));
        g2.drawOval(x +55, y, 10, 10);
        g2.drawLine(x +60, y + 10, x +60, y + 20);
        g2.drawLine(x +52, y + 13, x +68, y + 13);
        g2.drawLine(x +60, y + 20, x +65, y + 32);
        g2.drawLine(x +60, y + 20, x +55, y + 32);
    }
    
}
