/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

import bbj.graphicsobjects.Scene;
import java.util.ArrayList;
import java.util.Date;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

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
    
    /**
     * Метод проверки существования объекта в модели.
     * @param object Проверяемый объект.
     * @return TRUE если объект добавлен, иначе FALSE.
     */
    public boolean hasObject (UMLObject object) {
        boolean flag = true;
        
        if (m_objects.indexOf(object) == -1)
            flag = false;
        
        return flag;
    }
    
    /**
     * Метод удаления объекта из модели.
     * @param object Удаляемый объект.
     */
    public void removeObject (UMLObject object) {
        m_objects.remove(object);
    }
    
    /**
     * Метод удаления объекта из модели.
     * @param index Индекс удаляемого объекта.
     */
    public void removeObject (int index) {
        m_objects.remove(index);
    }
    
    /**
     * Метод изменения объекта в моделе.
     * @param object
     * @param index 
     */
    public void editObject (UMLObject object, int index) {
        m_objects.set(index, object);
    }
    
    /**
     * Метод сохранения аттрибутов файла.
     * @param doc Главный xml документ.
     * @param isDraft Черновая диаграмма или нет.
     * @return Элемент - аттрибуты файла.
     */
    public Element saveProperties (Document doc, boolean isDraft) {
        Element element = doc.createElement("properties");
        
        // Запись даты сохранения.
        element.appendChild(doc.createElement("create_date").appendChild(doc.createTextNode((new Date().toString()))));
        
        // Запись имени пользователя.
        element.appendChild(doc.createElement("author").appendChild(doc.createTextNode(System.getProperty("user.name"))));
        
        // Запись флага черновика.
        element.appendChild(doc.createElement("isDraft").appendChild(doc.createTextNode(Boolean.toString(isDraft))));
        
        return element;
    }
    
    /**
     * Метод проверки, является ли файл черновым.
     * @param filename Имя файла.
     * @return TRUE если файл черновой, иначе FALSE.
     */
    public boolean isDraft (String filename) {
        boolean flag = false;
        
        if (filename.matches("^.*\\.suefd$"))
            flag = true;
        
        return false;
    }
    
}
