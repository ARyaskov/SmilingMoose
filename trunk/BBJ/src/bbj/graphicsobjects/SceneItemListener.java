/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import bbj.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.*;
import java.util.*;

/**
 *
 * @author Alexander
 */
public class SceneItemListener implements MouseListener, MouseMotionListener {

    public static SceneItem m_currentSelectedItem;       // Текущий выделенный объект
    private int m_startX;               // Координата начала перетаскивания
    private int m_startY;               // Координата конца перетаскивания
    private SceneItem m_selectedItem;     // Перетаскиваемый коммент
    private int m_startYOnLine;
    private int endLine1;
    private int endLine2;
    
    /**
     * Конструктор с параметрами (используется всеми элементами сцены)
     * @param item Слушаемый элемент сцены
     */
    SceneItemListener(SceneItem item) {

        // Зануляем поля
        m_selectedItem = null;

        // Определяем тип текущего объекта и запоминаем его 
        if (item.getClass().getName().equals("bbj.graphicsobjects.UIFreeComment")) {
            m_selectedItem = (UIFreeComment) item;
        }
        else if (item.getClass().getName().equals("bbj.graphicsobjects.UIRectLifeLine")){
            m_selectedItem = (UIRectLifeLine) item;
        }
        else if (item.getClass().getName().equals("bbj.graphicsobjects.UIActorLifeLine")){
            m_selectedItem = (UIActorLifeLine) item;
        }
    }

    /**
     * Конструктор по умолчанию (используется сценой)
     */
    SceneItemListener() {
        // Зануляем поля
        m_selectedItem = null;
        endLine1 = 220;
        endLine2 = 230;
    }

    /**
     * Действия при клике на объект
     * @param e Данное событие мыши
     */
    @Override
    public void mouseClicked(MouseEvent e) {

        //Если кликнули больше одного раза
        if (e.getClickCount() > 1 && m_selectedItem != null) {
            m_selectedItem.edit(true);
            EditField f = new EditField(m_selectedItem);
            m_selectedItem.f = f;
        } else {
            mousePressed(e);
        }
    }

    /**
     * Действие при перемещении объекта мышью
     * @param e Данное событие мыши
     */
    @Override
    public void mouseDragged(MouseEvent e) {

        // Если объект существует
        if (m_selectedItem == null) {
            return;
        }
        int endX, endY;
        
        // Определяем координаты конца движения
        endX = e.getXOnScreen() - m_startX;
        
        // Проверим, что не вылезли за гграницы окна по Х
        endX = Math.max(endX, 0);
        endX = Math.min(endX, m_selectedItem.getParent().getWidth() - m_selectedItem.w);

        endY = e.getYOnScreen() - m_startY;

        // Проверим, что не вылезли за гграницы окна по Y
        endY = Math.max(endY, 0);
        endY = Math.min(endY, m_selectedItem.getParent().getHeight() - m_selectedItem.h); 
            
        if(m_selectedItem.getClass().getSuperclass().getName().equals("bbj.graphicsobjects.UILifeLine")){
            endY = 50;  // КОГДА ПОЯВЯТСЯ СООБЩЕНИЯ СОЗДАНИЯ ЗАМЕНИТЬ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        // ======================================================================\
            
            int asd = e.getY();
            if (m_startYOnLine>=endLine1 && m_startYOnLine<=endLine2){
                changeLifeLineLength((UILifeLine)m_selectedItem, asd);
            }
                
        }
        
        Rectangle rect = BBJ.app.getScene().getUIPanelsRectangle();
        //m_comment.setLocation(endX, endY);  // Задаем координаты объекту
//        if (rect.contains(endX, endY)) {
//            m_selectedItem.x = rect.x + rect.width + 2;
//            m_selectedItem.y = rect.y + rect.height + 2;
//        } else {
//            m_selectedItem.x = endX;
//            m_selectedItem.y = endY;
//        }

        // Задаем координаты
        m_selectedItem.x = endX;
        m_selectedItem.y = endY;

        m_selectedItem.updateUI();     // Перерисовываем объект

    }

    /**
     * Действия при нажатии на объект
     * @param e Данное событие мыши
     */
    @Override
    public void mousePressed(MouseEvent e) {
        
        // Снимаем выделение с прежнего объекта если он существует

        if (SceneItemListener.m_currentSelectedItem != null) {
            ArrayList<SceneItem> itemList = BBJ.app.getScene().getSceneObjects();
            Iterator it = itemList.iterator();
            while (it.hasNext()) {// Очищаем все элементы от выделения
                SceneItem cur = (SceneItem) it.next();
                cur.select(false);
                if (cur.isEdited()){
                    cur.f.setVisible(false);
                    cur.remove(cur.f);
                }
            }
        }

        // Если данный объект не сцена
        if (m_selectedItem == null) {
            return;
        }

        m_selectedItem.select(true);  // Выделяем объект
        
        endLine1 = m_selectedItem.h-75;
        endLine2 = m_selectedItem.h-65;  
        
        // Запоминаем выделенный объект
        SceneItemListener.m_currentSelectedItem = m_selectedItem;

        // Координаты щелчка мыши
        int x = e.getXOnScreen();
        int y = e.getYOnScreen();
        
        m_startYOnLine = e.getY();

        // Вычисляем координаты начала перетаскивания
        this.m_startX = x - m_selectedItem.x;
        this.m_startY = y - m_selectedItem.y;
        //SceneItemListener.currentSelectedItem.repaint();    // Перерисовываем
        BBJ.app.getScene().repaint();
    }
    
    /**
     * Изменить размер линии жизни
     * @param line Сама ЛЖ
     * @param newY Новая координата конца линии
     */
    public void changeLifeLineLength(UILifeLine line, int newY){
        if (newY >= 60){
            line.h = newY+70;
            line.setBounds(line.x, line.y, line.w, line.h);
        }
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
