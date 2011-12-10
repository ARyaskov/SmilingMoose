/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

import bbj.graphicsobjects.Point3D;
import java.util.ArrayList;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;

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
    private int m_index = 0; /** Поле индекса копии. */
    /** Флаг вида отрисовки линии жизни: 1 прямоугольник, 2 человечек. */
    private int m_style;
    
    /**
     * Метод задания стиля отрисовки линии жизни.
     * @param style Новый стиль отрисовки.
     */
    public void setDrawStyle (int style) {
        m_style = style;
    }
    
    /**
     * Метод получения стиля отрисовки линии жизни.
     * @return Индекс стиля отрисовки.
     */
    public int getDrawStyle () {
        return m_style;
    }
    
    /**
     * Метод смена индекса для копии.
     * @return Новый индекс.
     */
    private int incrementCopyIndex () {
        return ++m_index;
    }
    
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
     * Метод получения сообщения, принадлежащего линии жизни.
     * @param index Индекс сообщения.
     * @return Сообщение.
     */
    public Message get (int index) {
        return m_messages.get(index);
    }
    
    /**
     * Метод записи сообщения по индексу.
     * @param index Индекс сообщения.
     * @param message Записываемое сообщение.
     */
    public void set (int index, Message message) {
        m_messages.set(index, message);
    }
    
    /**
     * Метод получения количества сообщений.
     * @return Количество сообщений.
     */
    public int count () {
        return m_messages.size();
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
        m_messages = new ArrayList<Message>();
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
    
    /**
     * Метод записи линии жизни в xml файл.
     * @param document Главный документ файла.
     * @return Узел xml дерева.
     */
    @Override
    public Element write(Document document) {
        Element element = document.createElement("LifeLine");
        
        element.setAttribute("name", m_name);
        element.setAttribute("id", Integer.toString(m_fileId));
        element.setAttribute("is-end", Boolean.toString(m_isEnd));
        element.setAttribute("x", Double.toString(this.getCoordinates().getX()));
        element.setAttribute("y", Double.toString(this.getCoordinates().getY()));
        element.setAttribute("z", Double.toString(this.getCoordinates().getZ()));
        element.setAttribute("is-created", Boolean.toString(m_isCreated));
        element.setAttribute("is-destroyed", Boolean.toString(m_isDestroyed));
        element.setAttribute("index", Integer.toString(m_index));
        element.setAttribute("draw", Integer.toString(m_style));
        
        return element;
    }

    /**
     * Метод считывания объекта из файла.
     * @param node Текущий узел - элемент дерева.
     */
    @Override
    public void read(Node node) {
        double x,y,z;
        String buffer;
        NamedNodeMap attributes = node.getAttributes();
        // Считывание координаты z.
        Node attr = attributes.getNamedItem("z");
        buffer = attr.getNodeValue();
        z = Double.parseDouble(buffer);
        // Считывание координаты y.
        attr = attributes.getNamedItem("y");
        buffer = attr.getNodeValue();
        y = Double.parseDouble(buffer);
        // Считывание координаты x.
        attr = attributes.getNamedItem("x");
        buffer = attr.getNodeValue();
        x = Double.parseDouble(buffer);
        // Считывания идентификатора.
        attr = attributes.getNamedItem("id");
        buffer = attr.getNodeValue();
        this.setId(Integer.parseInt(buffer));
        // Считывание индекса для копий.
        attr = attributes.getNamedItem("index");
        buffer = attr.getNodeValue();
        m_index = Integer.parseInt(buffer);
        this.setCoordinates(new Point3D(x,y,z));
        // Считывание флага наличия конца.
        attr = attributes.getNamedItem("is-end");
        buffer = attr.getNodeValue();
        m_isEnd = Boolean.parseBoolean(buffer);
        // Считывание флага создания данной линии жизни.
        attr = attributes.getNamedItem("is-created");
        buffer = attr.getNodeValue();
        m_isCreated = Boolean.parseBoolean(buffer);
        // Считывание флага удаления данной линии жизни.
        attr = attributes.getNamedItem("is-destroyed");
        buffer = attr.getNodeValue();
        m_isDestroyed = Boolean.parseBoolean(buffer);
        // Считывание имени линии жизни.
        attr = attributes.getNamedItem("name");
        buffer = attr.getNodeValue();
        m_name = buffer;
        // Считывание стиля отрисовки лж.
        attr = attributes.getNamedItem("draw");
        buffer = attr.getNodeValue();
        m_style = Integer.parseInt(buffer);
    }
    
    /**
     * Метод создания копии текущей линии жизни.
     * @return Копия текущей линии жизни.
     */
    public LifeLine copy() {
        
        String d = this.getName();
        LifeLine ll = new LifeLine();
        
        // Создание нового имени.
        if (d.matches("^.*_copy[0-9]+$")) {
            d.replaceAll("_copy[0-9]+$", "_copy" + Integer.toString(this.incrementCopyIndex()));
        } else {
            d += "_copy" + Integer.toString(this.incrementCopyIndex());
        }
        
        ll.setCoordinates(this.getCoordinates());
        ll.setDescription(this.getDescription());
        
        return ll;
    }
    
}
