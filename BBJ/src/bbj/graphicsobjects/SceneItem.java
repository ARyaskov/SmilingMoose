/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import javax.swing.JComponent;

/**
 * Класс графического отображения UML объектов.
 * Наследуется от AWT {@link java.awt.Graphics2D}.
 * @version 1.0
 */
abstract public class SceneItem extends JComponent {
    
    /* Поля класса. */
    
    /** Координата Х */
    int x;
    
    /** Координата У */
    int y;
    
    /** Ширина */
    int w;
    
    /** Высота */
    int h;
        
    /** Флаг выбора объекта фокусом. */
    protected boolean m_isSelected; 
            
    /**
     * Выбрать объект
     * @param flag Выбран ли объект
     */
    public void select(boolean flag){
        m_isSelected = flag;
    }
    
    /**
     * Вернуть текущие координаты.
     * @return Координаты объекта
     */
    public Point3D getCoordinates(){
        Point3D crds = new Point3D(this.getX(), this.getY(), 0);
        return crds;
    }

}
