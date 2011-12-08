/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

import bbj.graphicsobjects.Point3D;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;

/**
 * Класс свободного комментария.
 * Наследуется от UMLObjects.
 * @see {@link uml.virtualobjects.UMLObjects}
 * @version 1.2
 */
public class FreeComment extends UMLObject {
    
    /* Поля класса. */
    private int m_index = 0; /** Поле индекса копии. */
    
    /**
     * Метод смена индекса для копии.
     * @return Новый индекс.
     */
    private int incrementCopyIndex () {
        return ++m_index;
    }
    
    /**
     * Конструктор с параметрами.
     */
    public FreeComment () {
        this.setDescription("");
        this.setId(0);
    }
    
    /**
     * Конструктор с параметрами.
     * @param str Описание комментария.
     * @param id Идентификатор комментария.
     */
    public FreeComment (String str, int id) {
        this.setDescription(str);
        this.setId(id);
    }

    /**
     * Метод записи комментария в xml файл.
     * @param document Главный документ файла.
     * @return Узел xml дерева.
     */
    @Override
    public Element write(Document document) {
        Element element = document.createElement("comment");
        
        element.appendChild(document.createTextNode(this.getDescription()));
        
        element.setAttribute("x", Double.toString(this.getCoordinates().getX()));
        element.setAttribute("y", Double.toString(this.getCoordinates().getY()));
        element.setAttribute("z", Double.toString(this.getCoordinates().getZ()));
        element.setAttribute("id", Integer.toString(this.getId()));
        element.setAttribute("index", Integer.toString(m_index));
        
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
        // Считывание описания.
        buffer = node.getTextContent();
        this.setDescription(buffer);
        // Считывания идентификатора.
        attr = attributes.getNamedItem("id");
        buffer = attr.getNodeValue();
        this.setId(Integer.parseInt(buffer));
        // Считывание индекса для копий.
        attr = attributes.getNamedItem("index");
        buffer = attr.getNodeValue();
        m_index = Integer.parseInt(buffer);
        this.setCoordinates(new Point3D(x,y,z));
    }
    
    /**
     * Метод сравнения свободных комментариев.
     * @param other Сравниваемый комментарий.
     * @return TRUE если объекты равны, иначе FALSE.
     */
    @Override
    public boolean equal (UMLObject other) {
        boolean flag = true;
        
        if (other.getClass() != FreeComment.class)
            flag = false;
        else
            if (!this.getDescription().equals(other.getDescription()) ||
                this.getId() != other.getId())
                flag = false;
        
        return flag;
    }

    /**
     * Метод создания копии текущего комментария.
     * @return Копия текущего комментария.
     */
    public FreeComment copy() {
        FreeComment fc = new FreeComment();
        String d = this.getDescription();
        
        // Создание нового имени.
        if (d.matches("^.*_copy[0-9]+$")) {
            d.replaceAll("_copy[0-9]+$", "_copy" + Integer.toString(this.incrementCopyIndex()));
        } else {
            d += "_copy" + Integer.toString(this.incrementCopyIndex());
        }
        
        fc.setDescription(d);
        fc.setCoordinates(getCoordinates());
        
        return fc;
    }
}