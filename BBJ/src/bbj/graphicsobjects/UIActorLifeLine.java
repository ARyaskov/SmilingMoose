/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.MenuItem;
import java.awt.Polygon;
import java.awt.PopupMenu;
import java.awt.Stroke;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 *
 * @author Alexander
 */
public class UIActorLifeLine extends UILifeLine {

    /** Номер экзампляра данного класса на сцене */
    public static int m_localNumber = 0;
    
    UIActorLifeLine(int x, int y){
        
        fillData(x,y);
        setDefaultName();
                
        SceneItemListener listener = new SceneItemListener(this);

        this.addMouseListener(listener);
        this.addMouseMotionListener(listener);
//        this.addKeyListener(listener);
        this.setToolTipText("Исполнитель: " + m_text);
        m_menu = new PopupMenu("Stop");
        m_stop = new MenuItem("Остановить");
        m_menu.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                m_isEnded = !m_isEnded;
                bbj.BBJ.app.getScene().repaint();
            }
        });
        m_menu.add(m_stop);
        this.add(m_menu);
    }
            
    @Override
    public void specificPaint(Graphics g) {
        
        m_textCoordX = x+zoom(10);
        m_textCoordY = y+zoom(47);
        
        Graphics2D g2 = (Graphics2D)g;
                     
        if (m_isSelected)   // Рисуем границы полигона красным цветом
            g2.setColor(Color.red);
        else                // Рисуем границы полигона черным цветом
            g2.setColor(Color.black);
        
        if (m_isSelected){
            g2.setStroke(new BasicStroke(1));
            Polygon p = new Polygon();          // Полигон комментария

            p.addPoint(x, y);
            p.addPoint(x + (int)(120*SceneItem.m_SR), y);
            p.addPoint(x + (int)(120*SceneItem.m_SR), y + (int)(50*SceneItem.m_SR));
            p.addPoint(x, y + (int)(50*SceneItem.m_SR));

            g.drawPolygon(p);     
        }

        if (m_isSelected)   // Рисуем границы полигона красным цветом
            g2.setColor(Color.red);
        else                // Рисуем границы полигона черным цветом
            g2.setColor(Color.black);
                
        // Рисуем человечка
        g2.setStroke(new BasicStroke(3));
        g2.drawOval(x +zoom(55), y, zoom(10), zoom(10));
        g2.drawLine(x +zoom(60), y + zoom(10), x +zoom(60), y + zoom(20));
        g2.drawLine(x +zoom(52), y + zoom(13), x +zoom(68), y + zoom(13));
        g2.drawLine(x +zoom(60), y + zoom(20), x +zoom(65), y + zoom(32));
        g2.drawLine(x +zoom(60), y + zoom(20), x +zoom(55), y + zoom(32));
    }

    @Override
    protected void setDefaultName() {
        m_text = "Исполнитель " + Integer.toString(m_localNumber++);
    }
    
}
