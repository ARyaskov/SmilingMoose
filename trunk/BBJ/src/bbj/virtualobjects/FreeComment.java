/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

import bbj.graphicsobjects.Point3D;
import java.util.ArrayList;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

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
        Element element = document.createElement("Comment");
        
        element.appendChild(document.createTextNode(this.getDescription()));
        
        element.setAttribute("x", Double.toString(this.getCoordinates().getX()));
        element.setAttribute("y", Double.toString(this.getCoordinates().getY()));
        element.setAttribute("z", Double.toString(this.getCoordinates().getZ()));
        
        return element;
    }

    /**
     * Метод чтения комментария из xml файла.
     * @param element Узел xml дерева.
     */
    @Override
    public void read(Element element) {
        double x,y,z;
        
        x = Double.parseDouble(element.getAttribute("x"));
        y = Double.parseDouble(element.getAttribute("y"));
        z = Double.parseDouble(element.getAttribute("z"));
        
        this.setDescription(element.getTextContent());
        
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