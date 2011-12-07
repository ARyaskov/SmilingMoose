
package bbj.graphicsobjects;

import bbj.graphicsobjects.*;
import bbj.virtualobjects.*;

import java.awt.*;
import javax.swing.*;

/**
 * Абстрактный класс линии жизни
 * @author Lemon
 */
abstract public class UILifeLine extends SceneItem{
        
    /**
     * Отрисивка линии жизни
     * @param g Компонент, на котором рисуем
     */
    abstract public void paint(Graphics g);
}
