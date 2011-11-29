/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

/**
 * Класс простого сообщения.
 * Наследуется от Message.
 * @see {@link uml.virtualobjects.Message}
 * @version 1.0
 */
public class SimpleMessage extends Message {
    
    /* Поля класса */
    private boolean m_hasReply; /** Флаг, имеет ли сообщение ответ. */

    @Override
    public Element write(Document document) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void read(Element element) {
        throw new UnsupportedOperationException("Not supported yet.");
    }
    
}
