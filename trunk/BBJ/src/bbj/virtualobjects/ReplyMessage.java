/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

/**
 * Класс сообщения уничтожения.
 * Наследуется от Message.
 * @see {@link uml.virtualobjects.Message}
 * @version 1.0
 */
public class ReplyMessage extends Message {
    
    /* Поля класса. */
    private Message m_parent; /** Указатель на сообщеие, которому требуется ответ. */
    
    /**
     * Метод получения сообщения, которому требуется ответ.
     * @return Сообщеие, которому требуется ответ.
     */
    public Message getParent () {
        return m_parent;
    }
    
    /**
     * Метод задания сообщения, которому требуется ответ.
     * @param parent Сообщение, которому требуется ответ.
     */
    public void setParent (Message parent) {
        m_parent = parent;
    }
    
    /**
     * Конструктор по умолчанию.
     */
    public ReplyMessage () {
        this.setDescription("");
        this.setId(0);
        this.setParent(null);
        this.setReceiver(null);
        this.setDescription(null);
    }

    @Override
    public Element write(Document document) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void read(Element element) {
        throw new UnsupportedOperationException("Not supported yet.");
    }
    
}
