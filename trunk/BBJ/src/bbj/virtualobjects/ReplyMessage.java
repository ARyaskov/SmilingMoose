/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;

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
    
    /**
     * Конструктор с параметрами.
     * @param desc Описание сообщения.
     * @param id Идентификатор сообщения.
     * @param parent Родитель, инициирующий ответ.
     */
    public ReplyMessage (String desc, int id, Message parent) {
        this.setDescription(desc);
        this.setId(id);
        this.setParent(parent);
        this.setReceiver(parent.getReceiver());
        this.setSender(parent.getSender());
    }

    /**
     * Метод записи возвратного сообщения в xml файл.
     * @param document Главный документ файла.
     * @return Узел xml дерева.
     */
    @Override
    public Element write(Document document) {
        Element element = super.write(document);
        
        element.setAttribute("type", "reply");
        element.setAttribute("parent", Integer.toString(m_parent.getId()));
        
        return element;
    }

    /**
     * Метод чтения возвратного сообщения из xml файла.
     * @param element Узел xml дерева.
     */
//    @Override
    public void read(Node node) {
        super.read(node);
        String buffer;
        NamedNodeMap attributes = node.getAttributes();
        // Считывание родителя.
        Node attr = attributes.getNamedItem("parent");
        buffer = attr.getNodeValue();
        m_parent = new SimpleMessage();
        m_parent.setId(Integer.parseInt(buffer));
    }
    
}
