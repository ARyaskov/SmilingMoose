/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

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
     * Функция обрезания текста для записи его в графический объект.
     * @return Обрезанный текст.
     */
    public String changeText () {
        String result = "";
        String[] parse = this.getDescription().split("\n");
        ArrayList<String> qwe = new ArrayList();
        
        // Ограниченик по строкам.
        for (int i = 0; i < parse.length; i++) {
            if (parse[i].length() > 20) {
                String buf = parse[i].substring(0, 20);
                buf += "\n";
                qwe.add(buf);
                buf = parse[i].substring(21, parse[i].length());
                qwe.add(buf);
            }
            else qwe.add(parse[i]);
        }
        
        if (qwe.size() > 7) {
            parse = new String[7];
            for (int i = 0; i < 6; i++) {
                parse[i] = qwe.get(i);
            }
            parse[6] = "...";
        }
        else {
            parse = new String[qwe.size()];
            for (int i = 0; i < qwe.size(); i++) {
                parse[i] = qwe.get(i);
            }
        }
        
        for (int i = 0; i < parse.length; i++) {
            result += parse[i];
            if (i != parse.length - 1)
                result += "\n";
        }
        
        return result;
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
        
        // Сохранение координат
        
        return element;
    }

    /**
     * Метод чтения комментария из xml файла.
     * @param element Узел xml дерева.
     */
    @Override
    public void read(Element element) {
        this.setDescription(element.getAttribute("description"));
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
}