/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

import bbj.graphicsobjects.Point3D;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

/**
 * Абстрактный класс UML объектов.
 * Является суперклассом для всех объектов.
 * @version 1.0
 */
abstract public class UMLObject {
    /* Поля класса. */
    private int m_id; /** Идентификатор объекта. */
    private String m_description; /** Описание объекта. */
    private Point3D m_coordinates; /** Координаты объекта на сцене. */
    
    /**
     * Метод возврата идентификатора объекта.
     * @return Идентификатор объекта.
     */
    public int getId () {
        return m_id;
    }
    
    /**
     * Метод получения координат объекта.
     * @return Координаты объекта.
     */
    public Point3D getCoordinates () {
        return m_coordinates;
    }
    
    /**
     * Метод задания координат.
     * @param point Новая позиция объекта.
     */
    public void setCoordinates (Point3D point) {
        m_coordinates = point;
    }
    
    /**
     * Метод задания идентификатора объекта.
     * @param id Новый идентификатор объекта.
     */
    public void setId (int id) {
        m_id = id;
    }
    
    /**
     * Метод получения описания объекта.
     * @return Описание объекта.
     */
    public String getDescription () {
        return m_description;
    }
    
    /**
     * Метод задания описания объекта.
     * @param desc Новое описание объекта.
     */
    public void setDescription (String desc) {
        m_description = desc;
    }
    
    /**
     * Абстрактный метод сохранения объекта в файл.
     * @param doc Документ xml файла.
     * @return 
     */
    abstract public Element write (Document document);
    
    /**
     * Абстрактный метод считывания объекта из файла.
     * @param element Текущий узел - элемент дерева.
     */
    abstract public void read (Element element);
    
    /**
     * Конструктор по умолчанию.
     */
    protected UMLObject () {
        this.m_description = "";
        this.m_id = 0;
        this.m_coordinates = new Point3D();
    }
    
    /**
     * Конструктор с параметрами.
     * @param str Новое описание объекта.
     * @param val Новый идентификатор объекта.
     */
    protected UMLObject(String str, int val) {
        this.m_description = str;
        this.m_id = val;
        this.m_coordinates = new Point3D();
    }
    
    /**
     * Метод сравнения объектов.
     * @param other Сравниваемый объект.
     * @return TRUE если объекты равны, иначе FALSE.
     */
    public boolean equal (UMLObject other) {
        boolean flag = true;
        
        if (this.getClass() != other.getClass()) flag = false;
        else {
            if (!this.m_description.equals(other.m_description) ||
                this.m_id != other.m_id)
                flag = false;
        }

        return flag;
    }
}