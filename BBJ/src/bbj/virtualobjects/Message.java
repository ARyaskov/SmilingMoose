/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

import bbj.graphicsobjects.Point3D;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

/**
 * Абстрактный класс сообщений.
 * Является суперклассом для сообщений.
 * @version 1.0
 */
abstract public class Message extends UMLObject {

    /* Поля класса. */
    private LifeLine m_sender; /** Линия жизин - отправитель сообщения. */
    private LifeLine m_receiver; /** Линия жизни - приемник сообщения. */
    private String m_name; /** Имя линии жизни. */
    public int[] ids = new int[2]; /** Идентификаторы связанных линий жизни. */
    
    /**
     * Метод возвращающий имя сообщения.
     * @return Имя сообщения.
     */
    public String getName () {
        return m_name;
    }
    
    /**
     * Метод задания имени сообщения.
     * @param name Новое имя сообщения.
     */
    public void setName (String name) {
        m_name = name;
    }
    
    /**
     * Метод получения отправителя сообщения.
     * @return Линия жизни, отправитель сообщения.
     */
    public LifeLine getSender () {
        return m_sender;
    }
    
    /**
     * Метод задания отправителя сообщения.
     * @param other Линия жизни, новый отправитель сообщения.
     */
    public void setSender (LifeLine other) {
        m_sender = other;
    }
    
    /**
     * Метод получения приемника сообщения.
     * @return Линия жизни, приемник сообщения.
     */
    public LifeLine getReceiver () {
        return m_receiver;
    }
    
    /**
     * Метод задания приемника сообщения.
     * @param other Линия жизни, новый приемник сообщения.
     */
    public void setReceiver (LifeLine other) {
        m_receiver = other;
    }
    
    /**
     * Конструктор по умолчанию.
     */
    protected Message () {
        m_sender = null;
        m_receiver = null;
        m_name = "";
    }
    
    /**
     * Конструктор с параметром.
     * @param sender Новый отправитель сообщения.
     * @param receiver Новый приемник сообщения.
     */
    protected Message (String name, LifeLine sender, LifeLine receiver) {
        m_sender = sender;
        m_receiver = receiver;
        m_name = name;
    }
    
    /**
     * Метод записи линии жизни в xml файл.
     * @param document Главный документ файла.
     * @return Узел xml дерева.
     */
    @Override
    public Element write(Document document) {
        Element element = document.createElement("message");
        
        element.setAttribute("name",m_name);
        element.setAttribute("start_id", Integer.toString(m_sender.getFileId()));
        element.setAttribute("end_id", Integer.toString(m_receiver.getFileId()));
        element.setAttribute("x", Double.toString(this.getCoordinates().getX()));
        element.setAttribute("y", Double.toString(this.getCoordinates().getY()));
        element.setAttribute("z", Double.toString(this.getCoordinates().getZ()));
        
        return element;
    }
    
    /**
     * Метод чтения линии жизни из xml файла.
     * @param element Узел xml дерева.
     */
    @Override
    public void read(Element element) {
        
        double x,y,z;
        m_name = element.getAttribute("name");
        
        ids[0] = Integer.parseInt(element.getAttribute("start_id"));
        ids[1] = Integer.parseInt(element.getAttribute("end_id"));
        
        x = Double.parseDouble(element.getAttribute("x"));
        y = Double.parseDouble(element.getAttribute("y"));
        z = Double.parseDouble(element.getAttribute("z"));
        
        this.setCoordinates(new Point3D(x,y,z));
    }
}
