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
    
    public static SceneItem currentSelectedItem;       // Текущий выделенный объект
            
    private int m_startX;               // Координата начала перетаскивания
    
    private int m_startY;               // Координата конца перетаскивания
    
    private SceneItem selectedItem;     // Перетаскиваемый коммент
    
    /**
     * Конструктор с параметрами (используется всеми элементами сцены)
     * @param item Слушаемый элемент сцены
     */
    SceneItemListener(SceneItem item){
        
        // Зануляем поля
        selectedItem = null;
        selectedItem = null;

        // Определяем тип текущего объекта и запоминаем его 
        if (item.toString().contains("UIFreeComment")){
            selectedItem = (UIFreeComment)item;
        }
    }
    
    /**
     * Конструктор по умолчанию (используется сценой)
     */
    SceneItemListener(){
        
        // Зануляем поля
        selectedItem = null;
        selectedItem = null;
    }
    
    @Override
    public void mouseClicked(MouseEvent e) {

    }
    
    /**
     * Действие при перемещении объекта мышью
     * @param e Данное событие мыши
     */
    @Override
    public void mouseDragged(MouseEvent e) {
        
        // Если объект существует
        if (selectedItem == null)
            return;
        
        // Определяем координаты конца движения
        int endX = e.getXOnScreen() - m_startX;
        int endY = e.getYOnScreen() - m_startY;
        
        // Проверим, что не вылезли за гграницы окна по Х
        endX = Math.max(endX, 0);
        endX = Math.min(endX, selectedItem.getParent().getWidth() - selectedItem.w);
        
        // Проверим, что не вылезли за гграницы окна по Y
        endY = Math.max(endY, 0);
        endY = Math.min(endY, selectedItem.getParent().getHeight() - selectedItem.h);
        
        // Задаем координаты
        selectedItem.x = endX;
        selectedItem.y = endY;
        
        selectedItem.repaint();     // Перерисовываем объект
    }

    /**
     * Действия при нажатии на объект
     * @param e Данное событие мыши
     */
    @Override
    public void mousePressed(MouseEvent e) {

        // Снимаем выделение с прежнего объекта если он существует
        if (SceneItemListener.currentSelectedItem != null){
            SceneItemListener.currentSelectedItem.select(false);// Ставим флаг
            SceneItemListener.currentSelectedItem.repaint();    // Перерисовываем
            SceneItemListener.currentSelectedItem = null;       // Зануляем
        }
                
        // Если данный объект не сцена
        if (selectedItem == null)
            return;
                
        selectedItem.select(true);  // Выделяем объект
        
        // Запоминаем выделенный объект
        SceneItemListener.currentSelectedItem = selectedItem;
        
        // Координаты щелчка мыши
        int x = e.getXOnScreen();
        int y = e.getYOnScreen();

        // Вычисляем координаты начала перетаскивания
        this.m_startX = x - selectedItem.x;
        this.m_startY = y - selectedItem.y;
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
