/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import javax.swing.JPanel;

/**
 * Класс графического отображения UML объектов.
 * Наследуется от AWT {@link java.awt.Graphics2D}.
 * @version 1.0
 */
abstract public class SceneItem extends JPanel {
    
    /* Поля класса. */
    
    /** Координата Х */
    protected int x;
    
    /** Координата У */
    protected int y;
    
    /** Ширина */
    protected int w;
    
    /** Высота */
    protected int h;
        
    /** Флаг выбора объекта фокусом. */
    protected boolean m_isSelected; 
            
    /** Флаг выбора режима просмотр/редактирование */
    protected boolean m_isEdit;
    
    /** Текст элемента. */
    protected String m_text;
    
    /**
     * Получить текст элемента
     * @return Текст
     */
    public String getText(){
        return m_text;
    }
    
    /**
     * Задать текст элементу
     * @param text новый текст
     */
    public void setText(String text){
        m_text = text;
    }
    
    /**
     * Выбрать объект
     * @param flag Выбран ли объект
     */
    public void select(boolean flag){
        m_isSelected = flag;
    }
    
    /**
     * Узнать, выделен ли объект
     * @return Результат
     */
    public boolean isSelected(){
        return m_isSelected;
    }
    
    /**
     * Узнать, редактируется ли объект
     * @return Результат
     */
    public boolean isEdited(){
        return m_isEdit;
    }
    
    /**
     * Редактировать объект
     * @param flag Редактируется ли объект
     */
    public void edit(boolean flag){
        m_isEdit = flag;
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
