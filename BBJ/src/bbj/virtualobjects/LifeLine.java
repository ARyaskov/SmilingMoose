/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

/**
 * Класс линии жизни.
 * Наследуется от UMLObjects.
 * @see {@link uml.virtualobjects.UMLObjects}
 * @version 1.0
 */
public class LifeLine extends UMLObject {

    /* Поля класса. */
    private String m_name; /** Имя/заголовок линии жизни. */
    private int    m_fileId; /** Идентификатор линии жизни, используемый при сохранении в xml файл. */
    private boolean m_isEnd; /** Имеет ли линия жизни конец. */
    private boolean m_isCreated; /** Флаг, была ли линия жизни создана другой линией жизни. */
    private boolean m_isDestroyed; /** Флаг, была ли линия жизни уничтожена другой линией жизни. */
    //private ArrayList<Message> m_messages; /** Массив сообщений, связанных с этой линией жизни. */
    
    /**
     * Конструктор по умолчанию.
     */
    public LifeLine () {
        this.setDescription("");
        this.setId(0);
        m_name = "";
        m_fileId = 0;
        m_isEnd = false;
        m_isCreated = false;
        m_isDestroyed = false;
        //m_messages = new ArrayList();
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
