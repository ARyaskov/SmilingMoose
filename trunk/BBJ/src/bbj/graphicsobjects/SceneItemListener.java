/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

/**
 *
 * @author Alexander
 */
public class SceneItemListener implements MouseListener, MouseMotionListener {
    
    private int m_startX;
    
    private int m_startY;
    
    private UIFreeComment m_comment;
    
    @Override
    public void mouseClicked(MouseEvent e) {

    }
    
    @Override
    public void mouseDragged(MouseEvent e) {
        
        if (m_comment == null)
            return;
        
       int endX = e.getXOnScreen() - m_startX;
       int endY = e.getYOnScreen() - m_startY;
        
        // Проверим, что не вылезли за гграницы окна по Х
        endX = Math.max(endX, 0);
        endX = Math.min(endX, m_comment.getParent().getWidth() - m_comment.w);
        
        // Проверим, что не вылезли за гграницы окна по Y
        endY = Math.max(endY, 0);
        endY = Math.min(endY, m_comment.getParent().getHeight() - m_comment.h);
        
        //m_comment.setLocation(endX, endY);  // Задаем координаты объекту
        m_comment.x = endX;
        m_comment.y = endY;
        
        m_comment.repaint();                // Перерисовываем объект
    }

    @Override
    public void mousePressed(MouseEvent e) {
           
        // Запоминаем текущий объект
        m_comment = (UIFreeComment)e.getSource();
       // c.x = c.x+10;
       // c.y = c.y+10;
       // c.repaint();
      
        // Координаты щелчка мыши
        int x = e.getXOnScreen();
        int y = e.getYOnScreen();
        
        // Вычисляем координаты начала перетаскивания
        this.m_startX = x - m_comment.x;
        this.m_startY = y - m_comment.y;
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        
    }

    @Override
    public void mouseEntered(MouseEvent e) {
        
    }

    @Override
    public void mouseExited(MouseEvent e) {
       
    }

    @Override
    public void mouseMoved(MouseEvent e) {

    }
    
}
