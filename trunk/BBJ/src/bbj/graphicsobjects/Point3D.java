/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import java.awt.Point;

/**
 * Класс точки в трехмерных координатах.
 * Наследуется от стандартного класса AWT: {@link java.awt.Point}.
 * @version 1.0
 */
public class Point3D extends Point {
    
    /* Поля класса. */
    private double m_z; /** Координата Z. */
    
    /**
     * Метод получения координаты Z.
     * @return Координата Z.
     */
    public double getZ() {
        return m_z;
    }
    
    /**
     * Метод задания координаты Z.
     * @param val Новое значение координаты Z.
     */
    public void setZ(double val) {
        m_z = val;
    }
    
}
