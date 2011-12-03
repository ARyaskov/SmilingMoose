/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

/**
 * Класс графического отображения UML объектов.
 * Наследуется от AWT {@link java.awt.Graphics2D}.
 * @version 1.0
 */
abstract public class SceneItem {
    
    /* Поля класса. */
    private Point3D m_coordinate; /** Координата объекта. */
    private boolean m_isSelected; /** Флаг выбора объекта фокусом. */
}
