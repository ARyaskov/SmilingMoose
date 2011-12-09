
package bbj.graphicsobjects;

import java.awt.*;
import javax.swing.JPanel;
import java.util.*;

/**
 * Класс графического отображения UML объектов.
 * Наследуется от AWT {@link java.awt.Graphics2D}.
 * @version 1.0
 */
abstract public class SceneItem extends JPanel {

    /* Поля класса. */
    
    EditField f;
            
    /** Координата Х */
    protected int x;
    /** Координата У */
    protected int y;
    /** Ширина */
    protected int w;
    /** Высота */
    protected int h;
    /** Флаг выбора объекта фокусом. */
    protected boolean m_isSelected;
    protected Rectangle m_rect;
    protected ArrayList<SelectEventListener> m_listenersList;
    //  protected ArrayList<ISceneSelectionListener> m_listListeners;

    public SceneItem() {
        m_listenersList = new ArrayList<SelectEventListener>();
        m_rect = new Rectangle(this.getX(), this.getY(), this.getWidth(), this.getHeight());
        addSelectionHappenedListener(new SelectSlot());
    }
    /** Флаг выбора режима просмотр/редактирование */
    protected boolean m_isEdit;
    /** Текст элемента. */
    protected String m_text;

    /**
     * Получить текст элемента
     * @return Текст
     */
    public String getText() {
        return m_text;
    }

    /**
     * Задать текст элементу
     * @param text новый текст
     */
    public void setText(String text) {
        m_text = text;
    }

    /**
     * Выбрать объект
     * @param flag Выбран ли объект
     */
    public void select(boolean flag) {
        m_isSelected = flag;
    }

    /**
     * Узнать, выделен ли объект
     * @return Результат
     */
    public boolean isSelected() {
        return m_isSelected;
    }

    /**
     * Узнать, редактируется ли объект
     * @return Результат
     */
    public boolean isEdited() {
        return m_isEdit;
    }

    /**
     * Редактировать объект
     * @param flag Редактируется ли объект
     */
    public void edit(boolean flag) {
        m_isEdit = flag;
    }

    /**
     * Вернуть текущие координаты.
     * @return Координаты объекта
     */
    public Point3D getCoordinates() {
        Point3D crds = new Point3D(this.getX(), this.getY(), 0);
        return crds;
    }

    public void updateRect() {
        m_rect.setBounds(this.getX(), this.getY(), this.getWidth(), this.getHeight());
    }

    public interface SelectEventListener extends EventListener {

        void selectionHappened(Scene.SelectEvent e);

        void selectionCancelled(Scene.SelectEvent e);
    }

    class SelectSlot implements SceneItem.SelectEventListener {

        public void selectionHappened(Scene.SelectEvent e) {
            updateRect();
            if (e.selectedRect.contains(m_rect)) {
                select(true);
            } else {
                select(false);
            }
        }

        public void selectionCancelled(Scene.SelectEvent e) {
            select(false);
        }
    }

    synchronized public SelectEventListener getFirstListener() {
        return m_listenersList.get(0);
    }

    synchronized public void addSelectionHappenedListener(SelectEventListener l) {
        m_listenersList.add(l);
    }

    synchronized public void removeSelectionHappenedListener(SelectEventListener l) {
        m_listenersList.remove(l);
    }
}
