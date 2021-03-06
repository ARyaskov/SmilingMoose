/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

import bbj.graphicsobjects.Point3D;
import bbj.graphicsobjects.Scene;
import bbj.virtualobjects.SimpleMessage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.w3c.dom.Text;
import org.xml.sax.SAXException;

/**
 * Класс виртуальной модели.
 * Является виртуальным отображеием графической модели.
 * @version 1.0
 */
public class VirtualModel {
    
    /* Поля класса. */
    private Scene m_scene; /** Указатель на графическое представление диаграммы. */
    private ArrayList<UMLObject> m_objects; /** Контейнер объектов диаграммы. */
    
    /**
     * Конструктор по умочанию.
     */
    public VirtualModel () {
        m_scene = null;
        m_objects = new ArrayList();
    }
    
    /**
     * Конструктор с параметром.
     * @param scene Ссылка на сцену - графическое отображение диаграммы.
     */
    public VirtualModel (Scene scene) {
        m_scene = scene;
        m_objects = new ArrayList();
    }
    
    /**
     * Метод получения ссылки на сцену.
     * @return Ссылка на сцену.
     */
    public Scene getScene () {
        return m_scene;
    }
    
    /**
     * Метод задания ссылки на сцену.
     * @param scene Ссылка на новую сцену.
     */
    public void setScene (Scene scene) {
        m_scene = scene;
    }
    
    /**
     * Метод добавления объекта в модель.
     * @param object Добавляемый объект.
     */
    public void addObject (UMLObject object) {
        m_objects.add(object);
    }
    
    /**
     * Метод получения объекта по индексу.
     * @param index Индекс, по которому получается объект.
     * @return Объект, полученный по индексу.
     */
    public UMLObject getObject (int index) {
        return m_objects.get(index);
    }
    
    /**
     * Метод проверки существования объекта в модели.
     * @param object Проверяемый объект.
     * @return TRUE если объект добавлен, иначе FALSE.
     */
    public boolean hasObject (UMLObject object) {
        boolean flag = true;
        
        if (m_objects.indexOf(object) == -1)
            flag = false;
        
        return flag;
    }
    
    /**
     * Метод удаления объекта из модели.
     * @param object Удаляемый объект.
     */
    public void removeObject (UMLObject object) {
        m_objects.remove(object);
    }
    
    /**
     * Метод удаления объекта из модели.
     * @param index Индекс удаляемого объекта.
     */
    public void removeObject (int index) {
        m_objects.remove(index);
    }
    
    /**
     * Метод изменения объекта в моделе.
     * @param object
     * @param index 
     */
    public void editObject (UMLObject object, int index) {
        m_objects.set(index, object);
    }
    
    /**
     * Метод сохранения аттрибутов файла.
     * @param doc Главный xml документ.
     * @param isDraft Черновая диаграмма или нет.
     * @return Элемент - аттрибуты файла.
     */
    private Element saveProperties (Document doc, boolean isDraft) {
        Element element = doc.createElement("properties");
        
        // Запись даты сохранения.
        Element createDate = doc.createElement("create_date");
        Text tnode1 = doc.createTextNode(new Date().toString());
        createDate.appendChild(tnode1);
        element.appendChild(createDate);
        
        // Запись имени пользователя.
        Element author = doc.createElement("author");
        Text tnode2 = doc.createTextNode(System.getProperty("user.name"));
        author.appendChild(tnode2);
        element.appendChild(author);
        
        // Запись флага черновика.
        Element isdraft = doc.createElement("isDraft");
        Text tnode3 = doc.createTextNode(Boolean.toString(isDraft));
        isdraft.appendChild(tnode3);
        element.appendChild(isdraft);
        
        return element;
    }
    
    /**
     * Метод проверки, является ли файл черновым.
     * @param filename Имя файла.
     * @return TRUE если файл черновой, иначе FALSE.
     */
    private boolean isDraft (String filename) {
        boolean flag = false;
        
        if (filename.matches("^.*\\.suefd$"))
            flag = true;
        
        return flag;
    }
    
    /**
     * Метод сохранения количества комментариев в xml файл.
     * @param doc Главный документ xml дерева.
     * @return Элемент, хранящий количество комментариев.
     */
    private Element getCommentsCount (Document doc) {
        Element element = doc.createElement("comments");
        int count = 0;
        
        for (int i = 0; i < m_objects.size(); i++) {
            if (m_objects.get(i).getClass() == FreeComment.class)
                count++;
        }
        
        element.setAttribute("count", Integer.toString(count));
        
        // Сохранение комментариев.
        if (count != 0) {
            for (int i = 0; i < m_objects.size(); i++) {
                if (m_objects.get(i).getClass() == FreeComment.class) {
                    //m_objects.get(i).setCoordinates(m_scene.get(i).getCoordinates());
                    element.appendChild(m_objects.get(i).write(doc));
                }
            }
        }
        
        return element;
    }
    
    /**
     * Метод сохранения количества линий жизни в xml файл.
     * @param doc Главный документ xml дерева.
     * @return Элемент, хранящий количество линий жизни.
     */
    private Element getLifeLinesCount (Document doc) {
        Element element = doc.createElement("lifelines");
        int count = 0;
        int id = 0;
        
        for (int i = 0; i < m_objects.size(); i++) {
            if (m_objects.get(i).getClass() == LifeLine.class)
                count++;
        }
        
        element.setAttribute("count", Integer.toString(count));
        
        // Сохранение линий жизни.
        if (count != 0) {
            for (int i = 0; i < m_objects.size(); i++) {
                if (m_objects.get(i).getClass() == LifeLine.class) {
                    //m_objects.get(i).setCoordinates(m_scene.get(i).getCoordinates());
                    ((LifeLine)m_objects.get(i)).setFileId(id);
                    element.appendChild(m_objects.get(i).write(doc));
                    id++;
                }
            }
        }
        
        return element;
    }
    
    /**
     * Метод сохранения количества сообщений в xml файл.
     * @param doc Главный документ xml дерева.
     * @return Элемент, хранящий количество линий жизни.
     */
    private Element getMessagesCount (Document doc) {
        Element element = doc.createElement("messages");
        int count = 0;
        
        for (int i = 0; i < m_objects.size(); i++) {
            if (m_objects.get(i).getClass() == Message.class ||
                m_objects.get(i).getClass() == CreateMessage.class ||
                m_objects.get(i).getClass() == DestroyMessage.class ||
                m_objects.get(i).getClass() == SimpleMessage.class ||
                m_objects.get(i).getClass() == ReplyMessage.class)
                count++;
        }
        
        element.setAttribute("count", Integer.toString(count));
        
        // Сохранение сообщений.
        if (count != 0) {
            for (int i = 0; i < m_objects.size(); i++) {
                if (m_objects.get(i).getClass() == Message.class ||
                    m_objects.get(i).getClass() == CreateMessage.class ||
                    m_objects.get(i).getClass() == DestroyMessage.class ||
                    m_objects.get(i).getClass() == SimpleMessage.class ||
                    m_objects.get(i).getClass() == ReplyMessage.class ||
                    m_objects.get(i).getClass() == AsynchronousMessages.class)
                {
                    //m_objects.get(i).setCoordinates(m_scene.get(i).getCoordinates());
                    element.appendChild(m_objects.get(i).write(doc));
                }
            }
        }
        
        return element;
    }
    
    /**
     * Метод сохранения диаграммы в файл.
     * @param filename 
     */
    public void save (String filename) throws ParserConfigurationException, SAXException, IOException, TransformerConfigurationException, TransformerException {
        
        DocumentBuilderFactory fact = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = fact.newDocumentBuilder();
        Document doc = builder.newDocument();
        
        Element root = doc.createElement("root");
        
        // Сохранение свойтв проекта.
        root.appendChild(this.saveProperties(doc, this.isDraft(filename)));
        // Сохранение объектов.
        Element element = doc.createElement("diagram");
        
        element.setAttribute("total_count", Integer.toString(this.m_scene.takeId()));
        
        Element comments = getCommentsCount(doc);
        Element lifelines = getLifeLinesCount(doc);
        Element messages = getMessagesCount(doc);
        
        element.appendChild(comments);
        element.appendChild(lifelines);
        element.appendChild(messages);

        root.appendChild(element);
        
        doc.appendChild(root);
        
        TransformerFactory transformerFactory = TransformerFactory.newInstance();
        Transformer transformer = transformerFactory.newTransformer();
        DOMSource source = new DOMSource(doc);
        StreamResult result = new StreamResult(new File(filename));

        transformer.transform(source, result);
        
    }
    
    /**
     * Метод загрузки модели из файла.
     * @param filename Имя чмиаемого файла.
     */
    public void load (String filename) throws ParserConfigurationException, SAXException, IOException {
        DocumentBuilderFactory f = DocumentBuilderFactory.newInstance();
        f.setValidating(false);
        DocumentBuilder builder = f.newDocumentBuilder();
        Document doc = builder.parse(new File(filename));
        
        NodeList nodes = doc.getChildNodes();
        nodes = nodes.item(0).getChildNodes();
        Node node = nodes.item(1);
        
        String buffer;
        NamedNodeMap attributes = node.getAttributes();
        Node attr = attributes.getNamedItem("total_count");
        buffer = attr.getNodeValue();
        m_scene.setId(Integer.parseInt(buffer));
        
        nodes = nodes.item(1).getChildNodes();
        
        for (int i = 0; i < nodes.getLength(); i++) {
            
            if("comments".equals(nodes.item(i).getNodeName())) {
                loadComments(nodes.item(i));
            } else if ("lifelines".equals(nodes.item(i).getNodeName())) {
                loadLifeLines(nodes.item(i));
            } else if ("messages".equals(nodes.item(i).getNodeName())) {
                this.readMessages(nodes.item(i));
            }
        }
        
        syncReply ();

    }
    
    /**
     * Метод считывания сободных комментариев.
     * @param node 
     */
    private void loadComments(Node node) {
        
        NodeList nodes = node.getChildNodes();
        
        for (int i = 0; i < nodes.getLength(); i++) {
            FreeComment fc = new FreeComment();
            fc.read(nodes.item(i));
            
            this.m_objects.add(fc);

        }
    }
    
    /**
     * Метод загрузки линий жизни.
     * @param node 
     */
    private void loadLifeLines (Node node) {
        
        NodeList nodes = node.getChildNodes();
        
        for (int i = 0; i < nodes.getLength(); i++) {
            LifeLine fc = new LifeLine();
            fc.read(nodes.item(i));
            
            this.m_objects.add(fc);

        }
    }
    
    /**
     * Метод загрузки сообщений.
     * @param node Узел дерева.
     */
    private void readMessages (Node node) {
        NodeList list = node.getChildNodes();
        
        for (int i = 0; i < list.getLength(); i++) {
            NamedNodeMap attributes = list.item(i).getAttributes();
            Node cAttrib = attributes.getNamedItem("type");
            String buf = cAttrib.getNodeValue();
            
            if ("simple".equals(buf)) {
                SimpleMessage sm = new SimpleMessage();
                sm.read(list.item(i));
                m_objects.add(sm);
                syncMessages(sm);
            } else if ("create".equals(buf)) {
                CreateMessage cm = new CreateMessage();
                cm.read(list.item(i));
                m_objects.add(cm);
                syncMessages(cm);
            } else if ("destroy".equals(buf)) {
                DestroyMessage dm = new DestroyMessage();
                dm.read(list.item(i));
                m_objects.add(dm);
                syncMessages(dm);
            } else if ("reply".equals(buf)) {
                ReplyMessage rm = new ReplyMessage();
                rm.read(list.item(i));
                m_objects.add(rm);
                syncMessages(rm);
            } else if ("asynch".equals(buf)) {
                AsynchronousMessages am = new AsynchronousMessages();
                am.read(list.item(i));
                m_objects.add(am);
                syncMessages(am);
            }
        }
    }
    
    /**
     * Метод синхронизации сообщений с связанными линиями жизни.
     * @param message Синхронизуемое сообщение.
     */
    private void syncMessages (Message message) {
        for (int i = 0; i < m_objects.size(); i++) {
            if (m_objects.get(i).getId() == message.ids[0]) {
                ((LifeLine)m_objects.get(i)).addMessage(message);
                message.setSender((LifeLine)m_objects.get(i));
            } else if (m_objects.get(i).getId() == message.ids[1]) {
                message.setReceiver((LifeLine)m_objects.get(i));
            }
        }
    }
    
    /**
     * Метод синхронизации сообщений возврата с другими сообщениями.
     */
    private void syncReply () {
        
        for (int i = 0; i < m_objects.size(); i++) {
            
            if (m_objects.get(i).getClass() == ReplyMessage.class) {
                
                for (int j = 0; j < m_objects.size(); j++) {
                    
                    if (m_objects.get(j).getId() == ((ReplyMessage)m_objects.get(i)).getParent().getId()) {
                        
                        ((ReplyMessage)m_objects.get(i)).setParent((Message)m_objects.get(j));
                        break;
                    }
                }
            }
        }
    }
    
    /**
     * Метод очистки модели
     */
    public void clear () {
        m_objects.clear();
    }
    
    /**
     * Метод получения количества объектов в модели.
     * @return Количество объектов в модели.
     */
    public int size () {
        return m_objects.size();
    }
    
}
