/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

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
    
}
