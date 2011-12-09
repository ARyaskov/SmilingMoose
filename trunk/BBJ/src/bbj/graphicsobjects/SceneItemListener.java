/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import bbj.*;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.*;
import java.awt.event.KeyListener;
import java.util.*;

/**
 *
 * @author Alexander
 */
public class SceneItemListener implements MouseListener, MouseMotionListener/*, KeyListener*/ {

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
        else if (item.getClass().getName().equals("bbj.graphicsobjects.UISimpleMessage")){
            m_selectedItem = (UISimpleMessage) item;
        }
        else if (item.getClass().getName().equals("bbj.graphicsobjects.UICreateMessage")){
            m_selectedItem = (UICreateMessage) item;
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
            //mousePressed(e);
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
            endY = m_selectedItem.y;
                                     
            
            int asd = e.getY();
            if (m_startYOnLine>=endLine1 && m_startYOnLine<=endLine2){
                changeLifeLineLength((UILifeLine)m_selectedItem, asd);
            } 
        }
        else if (m_selectedItem.getClass().getSuperclass().getName().equals("bbj.graphicsobjects.UIMessage" )){
            
            // ограничиваем передвижение сообщения по оси У
            UIMessage currentMessage = (UIMessage)m_selectedItem;
            
            if (endY >= currentMessage.getSender().getHeight()){
                endY = currentMessage.getSender().getHeight();
            }

            if (endY <= currentMessage.getSender().getY()+70){
                endY = currentMessage.getSender().getY()+70;
            }
               
            if (!currentMessage.getClass().getName().equals("bbj.graphicsobjects.UICreateMessage" )){
                if (endY >= currentMessage.getReceiver().getHeight()){
                    endY = currentMessage.getReceiver().getHeight();
                }

                if (endY <= currentMessage.getReceiver().getY()+70){
                    endY = currentMessage.getReceiver().getY()+70;
                }
            }
            else {
                if (endY-25 <= currentMessage.m_receiver.dotCoord-currentMessage.m_receiver.y-55)
                    currentMessage.m_receiver.y = endY-25;
                    
                else
                    endY = currentMessage.m_receiver.dotCoord-currentMessage.m_receiver.y-30;
                

            }
        }

        Rectangle rect = BBJ.app.getScene().getUIPanelsRectangle();
        //m_comment.setLocation(endX, endY);  // Задаем координаты объекту

        if (rect.contains(endX, endY)) {
           
            m_selectedItem.x = rect.x + rect.width + 2;
            m_selectedItem.y = rect.y + rect.height + 2;
        } else {
            m_selectedItem.x = endX;
            m_selectedItem.y = endY;
        }

        m_selectedItem.updateUI();     // Перерисовываем объект

    }

    /**
     * Действия при нажатии на объект
     * @param e Данное событие мыши
     */
    @Override
    public void mousePressed(MouseEvent e) {

        Scene scene = BBJ.app.getScene();
        if (e.getButton() == MouseEvent.BUTTON3) {
            scene.m_isCTRLPressed = true;
        } else if (e.getButton() == MouseEvent.BUTTON1) {
            scene.m_isCTRLPressed = false;
        }

        if (!scene.m_isCTRLPressed) {
            scene.getSelectedObjects().clear();
            /*if (SceneItemListener.m_currentSelectedItem != null)
                scene.addToSelectedObjects(m_selectedItem);*/
            /*if (!scene.isMultipleSelection()) {
                // Снимаем выделение с прежнего объекта если он существует

                if (SceneItemListener.m_currentSelectedItem != null) {

                    ArrayList<SceneItem> itemList = scene.getSceneObjects();
                    Iterator it = itemList.iterator();
                    while (it.hasNext()) {// Очищаем все элементы от выделения
                        SceneItem cur = (SceneItem) it.next();
                        cur.select(false);
                     if (cur.isEdited()){
    =======
            */
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
                    scene.getSelectedObjects().clear();
                    return;

                }

                endLine1 = m_selectedItem.h-75;
                endLine2 = m_selectedItem.h-65;  

                m_selectedItem.select(true);  // Выделяем объект

                // Запоминаем выделенный объект
                SceneItemListener.m_currentSelectedItem = m_selectedItem;
                scene.addToSelectedObjects(m_selectedItem);

                // Координаты щелчка мыши
                int x = e.getXOnScreen();
                int y = e.getYOnScreen();

                m_startYOnLine = e.getY();

                // Вычисляем координаты начала перетаскивания
                this.m_startX = x - m_selectedItem.x;
                this.m_startY = y - m_selectedItem.y;
                //SceneItemListener.currentSelectedItem.repaint();    // Перерисовываем
                endLine1 = m_selectedItem.h-25 - m_selectedItem.y;
            endLine2 = m_selectedItem.h-15 - m_selectedItem.y;  
        
            m_selectedItem.select(true);  // Выделяем объект
        } else {
            // Если данный объект не сцена
                if (m_selectedItem == null) {
                    scene.getSelectedObjects().clear();
                    return;

                }
                
                if (m_selectedItem.m_isSelected) {
                    for (int i = 0; i < scene.getSizeSelectedObjects(); i++) {
                        if (scene.getSelectedObjects().get(i).equals(m_selectedItem)) {
                            scene.getSelectedObjects().get(i).select(false);
                            scene.getSelectedObjects().remove(i);
                        }
                    }
                } else {
                
                    m_selectedItem.select(true);  // Выделяем объект
                    SceneItemListener.m_currentSelectedItem = m_selectedItem;
                }
            }
            
            if (!scene.getSelectedObjects().contains(m_selectedItem))
                scene.addToSelectedObjects(m_selectedItem);
            scene.repaint();
    }
    
    /**
     * Изменить размер линии жизни
     * @param line Сама ЛЖ
     * @param newY Новая координата конца линии
     */
    public void changeLifeLineLength(UILifeLine line, int newY){
        if (newY >= 70){
            boolean isOk = true;
            
            if (line.y > 50)
                newY +=line.y -50;
            
            Iterator<UIMessage>i = line.m_inbox.iterator();
            
            while(i.hasNext()){
               UIMessage buf = i.next();
               if (newY <= buf.getY()+buf.getHeight()-50)
                   isOk = false;
            }
            
            if (isOk){
                i= line.m_outbox.iterator();

                while(i.hasNext()){
                   UIMessage buf = i.next();
                   if (newY <= buf.getY()+buf.getHeight()-50)
                       isOk = false;
                }
            }
            
            if (isOk){
                line.h = newY+70;
                line.dotCoord = line.h; 
                line.setBounds(line.x, line.y, line.w, line.h);
            }
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

//    @Override
//    public void keyTyped(KeyEvent e) {
//        
//    }
//
//    @Override
//    public void keyPressed(KeyEvent e) {
//        if (e.getKeyCode() == KeyEvent.VK_CONTROL) {
//            Scene scene = BBJ.app.getScene();
//            scene.m_isCTRLPressed = true;
//        }
//    }
//
//    @Override
//    public void keyReleased(KeyEvent e) {
//        Scene scene = BBJ.app.getScene();
//        scene.m_isCTRLPressed = false;
//    }
}
