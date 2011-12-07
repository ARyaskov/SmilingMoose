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
        
        this.x = x;
        this.y = y;
        this.w = 120;
        this.h = 300;
        
        m_textCoordX = 10;
        m_textCoordY = 47;
        
        m_text = text;

        setBounds(x, y, w, h);
        this.m_isEdit = false;
        this.m_isSelected = false;

        SceneItemListener listener = new SceneItemListener(this);

        this.addMouseListener(listener);
        this.addMouseMotionListener(listener);
        this.setToolTipText("Исполнитель: " + m_text);
    }
            
    @Override
    public void specificPaint(Graphics g) {
        
        Graphics2D g2 = (Graphics2D)g;
                     
        if (m_isSelected)   // Рисуем границы полигона красным цветом
            g2.setColor(Color.red);
        else                // Рисуем границы полигона черным цветом
            g2.setColor(Color.black);
        
//        g2.setStroke(new BasicStroke(1));
//        Polygon p = new Polygon();          // Полигон комментария
//        
//        p.addPoint(x, y);
//        p.addPoint(x + 120, y);
//        p.addPoint(x + 120, y + 50);
//        p.addPoint(x, y + 50);
//        
//        g.drawPolygon(p);
        
        if (m_isSelected)   // Рисуем границы полигона красным цветом
            g2.setColor(Color.red);
        else                // Рисуем границы полигона черным цветом
            g2.setColor(Color.black);
                
        // Рисуем человечка
        g2.setStroke(new BasicStroke(3));
        g2.drawOval(55, 0, 10, 10);
        g2.drawLine(60, 10, 60, 20);
        g2.drawLine(52, 13, 68, 13);
        g2.drawLine(60, 20, 65, 32);
        g2.drawLine(60, 20, 55, 32);
    }
    
}
