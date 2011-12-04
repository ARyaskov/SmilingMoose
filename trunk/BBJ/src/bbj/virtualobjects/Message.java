/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

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
    
    @Override
    public Element write (Document doc) {
        Element element = doc.createElement("message");
        
        element.setAttribute("name","");
        
        return element;
    }
}
