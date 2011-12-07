/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

/**
 * Класс асинхронного сообщения.
 * Наследуется от Message.
 * @see {@link uml.virtualobjects.Message}
 * @version 1.0
 */
public class AsynchronousMessages extends Message {
    
    /**
     * Конструктор по умолчанию.
     */
    public AsynchronousMessages () {
        
        setDescription("");
        setId(0);
        setReceiver(null);
        setSender(null);
    }
    
    /**
     * Конструктор с параметрами.
     * @param desc Описание сообщения.
     * @param id Идентификатор сообщения.
     * @param send Отправитель сообщения.
     * @param recv Приемник сообщения.
     */
    public AsynchronousMessages (String desc, int id, LifeLine send, LifeLine recv) {
        
        setDescription(desc);
        setId(id);
        setSender(send);
        setReceiver(recv);
    }
    
    /**
     * Метод записи асинхронного сообщения в xml файл.
     * @param document Главный документ файла.
     * @return Узел xml дерева.
     */
    @Override
    public Element write(Document document) {
        Element element = super.write(document);
        
        element.setAttribute("type", "asynch");
        
        return element;
    }
    
    /**
     * Метод чтения асинхронные сообщения из xml файла.
     * @param element Узел xml дерева.
     */
    @Override
    public void read(Element element) {
        super.read(element);
    }
    
}
