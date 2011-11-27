/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

import java.util.ArrayList;
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
    private ArrayList<Message> m_messages; /** Массив сообщений, связанных с этой линией жизни. */
    
    /**
     * Метод получения имени.
     * @return Имя/заголовок линии жизни.
     */
    public String getName () {
        return m_name;
    }
    
    /**
     * Метод задания имени линии жизни.
     * @param name Новое имя линии жизни.
     */
    public void setName (String name) {
        m_name = name;
    }
    
    /**
     * Метод получения файлового идентификатора.
     * @return Файловый идентификатор.
     */
    public int getFileId () {
        return m_fileId;
    }
    
    /**
     * Метод задания файлового идентификатора.
     * @param id Новый файловый идентификатор.
     */
    public void setFileId (int id) {
        m_fileId = id;
    }
    
    /**
     * Метод получения наличия конца линии жизни.
     * @return Наличие у линии жизни конца.
     */
    public boolean hasEnd () {
        return m_isEnd;
    }
    
    /**
     * Метод задания наличия у линии жизни конца.
     * @param flag Значение наличия конца у линии жинзи.
     */
    public void setEnd (boolean flag) {
        m_isEnd = flag;
    }
    
    /**
     * Метод получения факта, создана линия жизни другой или нет.
     * @return TRUE если создана, иначе FALSE.
     */
    public boolean hasCreated () {
        return m_isCreated;
    }
    
    /**
     * Метод задания факта, создана линия жизни другой или нет.
     * @param flag Значение факта, создана линия жизни другой или нет.
     */
    public void setCreated (boolean flag) {
        m_isCreated = flag;
    }
    
    /**
     * Метод получения факта, уничтожена линия жизни другой или нет.
     * @return TRUE если уничтожена, иначе FALSE.
     */
    public boolean hasDestroyed () {
        return m_isDestroyed;
    }
    
    /**
     * Метод задания факта, уничтожена линия жизни другой или нет.
     * @param flag Значение факта, уничтожена линия жизни другой или нет.
     */
    public void setDestroyed (boolean flag) {
        m_isDestroyed = flag;
    }
    
    /**
     * Метод добавления сообщения к линии жизни.
     * @param message Добавляемое сообщение.
     */
    public void addMessage (Message message) {
        m_messages.add(message);
    }
    
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
        m_messages = new ArrayList();
    }
    
    /**
     * Конструктор с параметрами.
     * @param name Имя/заголовок линии жизни.
     * @param desc Описание линии жизни.
     * @param id Идентификатор линии жизни.
     */
    public LifeLine (String name, String desc, int id) {
        this.setDescription(desc);
        this.setId(id);
        m_name = name;
    }
    
    /**
     * Конструктор с параметрами.
     * @param desc Описание линии жизни.
     * @param id Идентификатор линии жизни.
     * @param name Имя линии жизни.
     * @param fid Файловый идентификатор линии жизни.
     * @param end Наличие конца лии жизни.
     * @param create Линия жизни создана другой линией жизни.
     * @param destr Линия жизни уничтожена линией жизни.
     * @param ms Связанные с линией жизни сообщения.
     */
    public LifeLine (String desc, int id, String name, int fid, boolean end, boolean create, boolean destr, ArrayList<Message> ms) {
        this.setDescription(desc);
        this.setId(id);
        m_name = name;
        m_fileId = fid;
        m_isEnd = end;
        m_isCreated = create;
        m_isDestroyed = destr;
        m_messages = new ArrayList(ms);
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
