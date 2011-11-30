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
    
    /**
     * Конструктор по умолчанию.
     */
    public Point3D () {
        super();
        m_z = 0;
    }
    
    /**
     * Конструктор с параметрами.
     * @param x Координата X.
     * @param y Координата Y.
     * @param z Координата Z.
     */
    public Point3D (double x, double y, double z) {
        super((int)x,(int)y);
        m_z = z;
    }
    
}
