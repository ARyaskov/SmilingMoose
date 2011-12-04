/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import java.awt.Graphics;

/**
 * Класс графического отображения UML объектов.
 * Наследуется от AWT {@link java.awt.Graphics2D}.
 * @version 1.0
 */
abstract public class SceneItem {
    
    /* Поля класса. */
    
    /** Координата объекта. */
    Point3D m_coordinates;
    
    /** Флаг выбора объекта фокусом. */
    boolean m_isSelected; 
    
    /**
     * Вернуть текущие координаты.
     * @return Координаты объекта
     */
    public Point3D getCoordinates(){
        return m_coordinates;
    }
    
    /**
     * Установить новые координаты
     * @param newCoordinates Объект новых координат
     */
    public void setCoordinates(Point3D newCoordinates){
        m_coordinates = newCoordinates;
    }
    
    /**
     * Выбрать объект
     * @param flag Выбран ли объект
     */
    public void select(boolean flag){
        m_isSelected = flag;
    }
    
    /**
     * Абстрактный метод отрисовки графического объекта
     * @param g Объект, на котором будем рисовать
     */
    abstract public void draw(Graphics g);
}
