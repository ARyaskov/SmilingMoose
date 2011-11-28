/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

import bbj.graphicsobjects.Scene;
import java.util.ArrayList;

/**
 * Класс виртуальной модели.
 * Является виртуальным отображеием графической модели.
 * @version 1.0
 */
public class VirtualModel {
    
    /* Поля класса. */
    private Scene m_scene; /** Указатель на графическое представление диаграммы. */
    private ArrayList<UMLObject> m_objects; /** Контейнер объектов диаграммы. */
    
    /**
     * Конструктор по умочанию.
     */
    public VirtualModel () {
        m_scene = null;
        m_objects = new ArrayList();
    }
    
    /**
     * Конструктор с параметром.
     * @param scene Ссылка на сцену - графическое отображение диаграммы.
     */
    public VirtualModel (Scene scene) {
        m_scene = scene;
        m_objects = new ArrayList();
    }
    
    /**
     * Метод получения ссылки на сцену.
     * @return Ссылка на сцену.
     */
    public Scene getScene () {
        return m_scene;
    }
    
    /**
     * Метод задания ссылки на сцену.
     * @param scene Ссылка на новую сцену.
     */
    public void setScene (Scene scene) {
        m_scene = scene;
    }
    
    /**
     * Метод добавления объекта в модель.
     * @param object Добавляемый объект.
     */
    public void addObject (UMLObject object) {
        m_objects.add(object);
    }
    
    /**
     * Метод получения объекта по индексу.
     * @param index Индекс, по которому получается объект.
     * @return Объект, полученный по индексу.
     */
    public UMLObject getObject (int index) {
        return m_objects.get(index);
    }
    
}
