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

    /**
     * Конструктор с параметрами (используется всеми элементами сцены)
     * @param item Слушаемый элемент сцены
     */
    SceneItemListener(SceneItem item) {

        // Зануляем поля
        m_selectedItem = null;

        // Определяем тип текущего объекта и запоминаем его 
        if (item.toString().contains("UIFreeComment")) {
            m_selectedItem = (UIFreeComment) item;
        }
        else if (item.toString().contains("UIRectLifeLine")){
            m_selectedItem = (UIRectLifeLine) item;
        }
        else if (item.toString().contains("UIActorLifeLine")){
            m_selectedItem = (UIActorLifeLine) item;
        }
    }

    /**
     * Конструктор по умолчанию (используется сценой)
     */
    SceneItemListener() {
        // Зануляем поля
        m_selectedItem = null;
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

        // Определяем координаты конца движения
        int endX = e.getXOnScreen() - m_startX;
        int endY = e.getYOnScreen() - m_startY;

        // Проверим, что не вылезли за гграницы окна по Х
        endX = Math.max(endX, 0);
        endX = Math.min(endX, m_selectedItem.getParent().getWidth() - m_selectedItem.w);

        // Проверим, что не вылезли за гграницы окна по Y
        endY = Math.max(endY, 0);
        endY = Math.min(endY, m_selectedItem.getParent().getHeight() - m_selectedItem.h);


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
 //               cur.updateUI();
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

        // Запоминаем выделенный объект
        SceneItemListener.m_currentSelectedItem = m_selectedItem;

        // Координаты щелчка мыши
        int x = e.getXOnScreen();
        int y = e.getYOnScreen();

        // Вычисляем координаты начала перетаскивания
        this.m_startX = x - m_selectedItem.x;
        this.m_startY = y - m_selectedItem.y;
        //SceneItemListener.currentSelectedItem.repaint();    // Перерисовываем
        BBJ.app.getScene().repaint();
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
