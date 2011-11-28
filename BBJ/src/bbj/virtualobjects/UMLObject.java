/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

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
    
    /**
     * Метод возврата идентификатора объекта.
     * @return Идентификатор объекта.
     */
    public int getId () {
        return m_id;
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
    }
    
    /**
     * Конструктор с параметрами.
     * @param str Новое описание объекта.
     * @param val Новый идентификатор объекта.
     */
    protected UMLObject(String str, int val) {
        this.m_description = str;
        this.m_id = val;
    }
}