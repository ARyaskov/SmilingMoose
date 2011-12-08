/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;

/**
 * Класс сообщения уничтожения.
 * Наследуется от Message.
 * @see {@link uml.virtualobjects.Message}
 * @version 1.0
 */
public class DestroyMessage extends Message {
    
    /* Поля класса */
    private boolean m_hasReply; /** Флаг, имеет ли сообщение ответ. */
    
    /**
     * Метод получения факта: имеет ли сообщение ответ.
     * @return TRUE если сообщение имеет ответ, иначе FALSE.
     */
    public boolean hasReply () {
        return m_hasReply;
    }
    
    /**
     * Метод задания факта: имеет ли сообщение ответ.
     * @param flag Значение факта.
     */
    public void setReply (boolean flag) {
        m_hasReply = flag;
    }
    
    /**
     * Конструктор с параметрами.
     */
    public DestroyMessage () {
        this.setDescription("");
        this.setId(0);
        this.setReceiver(null);
        this.setReply(false);
        this.setSender(null);
    }
    
    /**
     * Конструктор с параметрами.
     * @param desc Описанние сообщеия.
     * @param id Идентификатор сообщения.
     * @param send Отправитель сообщения.
     * @param recv Приемник сообщения.
     */
    public DestroyMessage (String desc, int id, LifeLine send, LifeLine recv) {
        this.setDescription(desc);
        this.setId(id);
        this.setSender(send);
        this.setReceiver(recv);
        m_hasReply = false;
    }

    /**
     * Метод записи сообщения уничтожения в xml файл.
     * @param document Главный документ файла.
     * @return Узел xml дерева.
     */
    @Override
    public Element write(Document document) {
        Element element = super.write(document);
        
        element.setAttribute("type", "destroy");
        element.setAttribute("parent", "-");
        
        return element;
    }

    /**
     * Метод чтения сообщения уничтожения из xml файла.
     * @param element Узел xml дерева.
     */
    @Override
    public void read(Node node) {
        super.read(node);
    }
    
}
