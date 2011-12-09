/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import bbj.virtualobjects.*;
import bbj.graphicsobjects.*;

import bbj.*;

import java.io.IOException;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.awt.geom.Rectangle2D;
import java.util.*;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import org.xml.sax.SAXException;

/**
 * Класс - сцена для отрисовки объектов диаграммы.
 *
 * @version 1.0
 */
public final class Scene extends JPanel {

    private boolean m_isGrid;
    private int m_gridFactor = 20;
    private Color m_gridColor = new Color(128, 128, 128, 64);
    private VirtualModel m_model;
    private ArrayList<SceneItem> m_objects;
    private String m_draggedNow;
    private ArrayList<String> itemsMessages;
    private ArrayList<String> itemsEntities;
    private boolean selectActivate;
    private boolean m_dragObjects;
    private int startSelect_x;
    private int startSelect_y;
    private int stopSelect_x;
    private int stopSelect_y;
    private Rectangle m_messageSelectorRect;
    private Rectangle m_entitySelectorRect;
    private Rectangle m_selectionRect;
    private ArrayList<SceneItem> m_selectedObjects;
    private int dx;
    private int dy;
    private int startDrag_x;
    private int startDrag_y;
    private int stopDrag_x;
    private int stopDrag_y;
    private boolean m_multiDragMode;
    private BBJ m_app;
    private int m_messageSelector_width;
    private int m_messageSelector_height;
    private int m_entitySelector_width;
    private int m_entitySelector_height;
    private int m_messageSelector_x;
    private int m_messageSelector_y;
    private int m_entitySelector_x;
    private int m_entitySelector_y;
    private int m_scene_height;
    private int m_scene_width;

    /**
     * Метод получения объекта сцены по индексу.
     *
     * @param index Индекс получаемого объекта.
     * @return Объект сцены.
     */
    public SceneItem get(int index) {
        return m_objects.get(index);
    }

    /**
     * Метод получения ссылки на модель.
     *
     * @return Модель.
     */
    public VirtualModel getModel() {
        return m_model;
    }

    /**
     * Конструктор по умолчанию.
     */
    public Scene(BBJ bbj) {
        super();
        m_app = bbj;
        m_isGrid = true;
        m_dragObjects = false;
        m_model = new VirtualModel();
        m_objects = new ArrayList<SceneItem>();
        m_selectedObjects = new ArrayList<SceneItem>();
        m_draggedNow = new String();
        selectActivate = false;
        startSelect_x = 0;
        startSelect_y = 0;
        stopSelect_x = 0;
        stopSelect_y = 0;
        m_selectionRect = new Rectangle();

        this.setDoubleBuffered(true);



        m_messageSelector_x = m_app.m_messageSelector.getX();
        m_messageSelector_y = m_app.m_messageSelector.getY() + 22;
        m_entitySelector_x = m_app.m_entitySelector.getX();
        m_entitySelector_y = m_app.m_entitySelector.getY() + 102;

        m_messageSelector_width = m_app.m_messageSelector == null ? 0
                : m_app.m_messageSelector.getWidth();
        m_messageSelector_height = m_app.m_messageSelector == null ? 0
                : m_app.m_messageSelector.getHeight();
        m_entitySelector_width = m_app.m_entitySelector == null ? 0
                : m_app.m_entitySelector.getWidth() + 5;
        m_entitySelector_height = m_app.m_entitySelector == null ? 0
                : m_app.m_entitySelector.getHeight();

        m_scene_height = m_app.mainFrame.getHeight();
        m_scene_width = m_app.mainFrame.getWidth();

        //this.setToolTipText("Диаграмма последовательности");

        this.addMouseListener(new MouseSlot());    // Добавляем слушателя мыши на сцену

        this.addMouseMotionListener(new MouseSlot());



        UIFreeComment testCommentChecked = new UIFreeComment(150, 200,
                "Linux работает на множестве архитектур, таких как "
                + "Intel x86, x86-64, PowerPC, ARM, Alpha AXP, Sun SPARC, Motorola 68000,"
                + " Hitachi SuperH, IBM S/390, MIPS, HP PA-RISC,"
                + " AXIS CRIS, Renesas M32R, Atmel AVR32, Renesas H8/300, NEC V850, Tensilica Xtensa и многих других.");

        // Добавляем тестовые объекты в контейнер       

        UIFreeComment testCommentChecked1 = new UIFreeComment(333, 333,
                "Процессоры Power PC также используются в многоядерных"
                + " процессорах в качестве управляющих ядер, например:");


        UIRectLifeLine ll = new UIRectLifeLine(470, 111, "Линия жизни 1");



        
        UIActorLifeLine al = new UIActorLifeLine(400, 333, "Исполнитель 1 тест");
                

        UISimpleMessage m = new UISimpleMessage(ll, al, 215, "Тестовое сообщение 1");



        ll.setEnded(true);
        this.add(m);
        this.add(ll);
        this.add(testCommentChecked1);
        this.add(testCommentChecked);
        this.add(al);

        // Добавляем тестовые объекты в контейнер
        m_objects.add(m);
        m_objects.add(ll);
        m_objects.add(testCommentChecked);
        m_objects.add(testCommentChecked1);
        m_objects.add(al);
        

        // Создаем сцене особого слушателя
        SceneItemListener sceneItemListener = new SceneItemListener();

        // Задаем сцене слушателя
        this.addMouseListener(sceneItemListener);


    }

    @Override
    protected void paintComponent(Graphics g) {

        super.setBackground(BBJ.app.m_background_color);
        Graphics2D g2 = (Graphics2D) g;


        /*
         * g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
         * RenderingHints.VALUE_ANTIALIAS_ON);
         * g2.setRenderingHint(RenderingHints.KEY_RENDERING,
         * RenderingHints.VALUE_RENDER_QUALITY);
         * g2.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING,
         * RenderingHints.VALUE_TEXT_ANTIALIAS_LCD_HRGB);
         * g2.setRenderingHint(RenderingHints.KEY_ALPHA_INTERPOLATION,
         * RenderingHints.VALUE_ALPHA_INTERPOLATION_QUALITY);
         * g2.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BICUBIC);
         */

        g.setColor(Color.WHITE);

        m_scene_width = m_app.mainFrame.getWidth();
        m_scene_height = m_app.mainFrame.getHeight();

        // далее непутёвый алгоритм закраски областей, в связи
        // с известными трудностями при перерисовке пришлось создать
        // такой
        // Закрашиваем большой квадрат справа от элементов
        g.fillRect(m_entitySelector_x + m_entitySelector_width,
                0,
                m_scene_width,
                m_scene_height);
        // Закрышиваем прямоугольник снизу от элементов
        g.fillRect(0,
                m_entitySelector_y + m_entitySelector_height + 3,
                m_scene_width,
                m_scene_height);
        // Красим между
        g.fillRect(0,
                m_messageSelector_y + m_messageSelector_height - 15,
                m_scene_width,
                10);
        /*
         * g.setColor(Color.BLACK);
         * g.drawLine(0,m_messageSelector_y+10,1200,m_messageSelector_y);
         g.setColor(Color.WHITE);
         */
        //красим сбоку
        g.fillRect(0,
                0,
                5,
                m_scene_height);
        //красим сверху
        g.fillRect(0,
                0,
                m_scene_width,
                7);



        if (m_isGrid) {
            makeGrid(g2);
        }



        // Отрисовываем все объекты сцены
        Iterator<SceneItem> i = m_objects.iterator();



        while (i.hasNext()) {
            i.next().paint(g);
        }


        m_app.repaintSelectors();

        if (selectActivate) {

            g2.setColor(new Color(0, 153, 255, 128));

            Stroke oldStroke = g2.getStroke();
            Stroke stroke = new BasicStroke(3);
            g2.setStroke(stroke);
            if (startSelect_x > stopSelect_x && startSelect_y > stopSelect_y) {
                g2.drawRect(stopSelect_x, stopSelect_y, startSelect_x - stopSelect_x, startSelect_y - stopSelect_y);
                m_selectionRect.setRect(stopSelect_x, stopSelect_y, startSelect_x - stopSelect_x, startSelect_y - stopSelect_y);
            } else if (startSelect_x > stopSelect_x && startSelect_y < stopSelect_y) {
                g2.drawRect(stopSelect_x, startSelect_y, startSelect_x - stopSelect_x, stopSelect_y - startSelect_y);
                m_selectionRect.setRect(stopSelect_x, startSelect_y, startSelect_x - stopSelect_x, stopSelect_y - startSelect_y);
            } else if (startSelect_x < stopSelect_x && startSelect_y > stopSelect_y) {
                g2.drawRect(startSelect_x, stopSelect_y, stopSelect_x - startSelect_x, startSelect_y - stopSelect_y);
                m_selectionRect.setRect(startSelect_x, stopSelect_y, stopSelect_x - startSelect_x, startSelect_y - stopSelect_y);
            } else if (startSelect_x < stopSelect_x && startSelect_y < stopSelect_y) {
                g2.drawRect(startSelect_x, startSelect_y, stopSelect_x - startSelect_x, stopSelect_y - startSelect_y);
                m_selectionRect.setRect(startSelect_x, startSelect_y, stopSelect_x - startSelect_x, stopSelect_y - startSelect_y);

            }
            g2.setStroke(oldStroke);
            Iterator it = m_objects.iterator();

            while (it.hasNext()) {
                SceneItem item = (SceneItem) it.next();
                if (m_selectionRect.contains(item.getBounds())) {
                    addToSelectedObjects(item);
                }
            }
            fireSelectionHappened();
        }
        if (false) {//не изменять, для теста
            Iterator it = m_selectedObjects.iterator();

            while (it.hasNext()) {
                SceneItem item = (SceneItem) it.next();

                item.setLocation(stopDrag_x, stopDrag_y);


            }
        }

    }

    public void setIsGrid(boolean _isGrid) {
        m_isGrid = _isGrid;
        repaint();
    }

    public void setGridFactor(int factor) {
        m_gridFactor = factor;
        repaint();
    }

    public void setGridColor(Color color) {
        m_gridColor = color;
        repaint();
    }

    public void addToSelectedObjects(SceneItem item) {
        m_selectedObjects.add(item);
    }

    public void removeFromSelectedObjects(SceneItem item) {
        m_selectedObjects.remove(item);
    }

    public int getSizeSelectedObjects() {
        return m_selectedObjects.size();
    }

    public ArrayList<SceneItem> getSelectedObjects() {
        return m_selectedObjects;
    }

    public Color getGridColor() {
        return m_gridColor;
    }

    public boolean getIsGrid() {
        return m_isGrid;
    }

    public int getGridFactor() {
        return m_gridFactor;
    }

    public ArrayList<SceneItem> getSceneObjects() {
        return m_objects;
    }

    public boolean isMultipleSelection() {
        return m_selectedObjects.size() > 1 ? true : false;
    }

    @Override
    public void setSize(int w, int h) {
        super.setSize(w, h);
        m_scene_width = w;
        m_scene_height = h;

    }

    public Rectangle getUIPanelsRectangle() {
        return new Rectangle(0,
                0,
                m_app.m_entitySelector.getWidth() + 13,
                m_app.m_entitySelector.getHeight() * 2 + 20);
    }

    protected void makeGrid(Graphics g) {

        g.setColor(m_gridColor);



        int i;

        for (i = 0; i < 200; i++) {
            if (m_entitySelector_y + m_entitySelector_height > m_gridFactor * i) {//Рисуем справа от панельки

                g.drawLine(m_entitySelector_x + m_entitySelector_width,
                        m_gridFactor * i,
                        m_scene_width,
                        m_gridFactor * i); // Горизонтальные
            } else {//Рисуем на всю ширину
                g.drawLine(0,
                        m_gridFactor * i,
                        m_scene_width,
                        m_gridFactor * i); // Горизонтальные
            }

            if (m_entitySelector_x + m_entitySelector_width > m_gridFactor * i) {//Рисуем под панелькой
                g.drawLine(m_gridFactor * i,
                        m_entitySelector_y + m_entitySelector_height,
                        m_gridFactor * i,
                        m_scene_height); // Вертикальные
            } else {
                g.drawLine(
                        m_gridFactor * i,
                        0,
                        m_gridFactor * i,
                        m_scene_height); // Вертикальные 
            }

            //   if (getUIPanelsRectangle().getBounds().contains(i, m_gridFactor * i))
        }


    }

    public SceneItem getOwnerItem(int x, int y) {
        SceneItem result = null;
        Iterator i = m_objects.iterator();
        SceneItem item;
        while (i.hasNext()) {
            item = (SceneItem) i.next();
            if (item.getBounds().contains(x, y)) {
                result = item;
                break;
            }
        }
        return result;
    }

    class MouseSlot implements MouseListener, MouseMotionListener {

        /**
         * Действие при клике мышью на сцену
         *
         * @param e Объект события
         */
        @Override
        public void mouseClicked(MouseEvent e) {
        }

        public void mouseEntered(MouseEvent e) {
        }

        public void mouseExited(MouseEvent e) {
        }

        public void mousePressed(MouseEvent e) {

            selectActivate = true;
            startSelect_x = e.getX();
            startSelect_y = e.getY();
            startDrag_x = e.getX();
            startDrag_y = e.getY();

            stopSelect_x = e.getX();
            stopSelect_y = e.getY();


            if ((m_selectedObjects.size() > 1) && (getOwnerItem(startSelect_x, startSelect_y) != null)) {
                m_multiDragMode = true;
                stopDrag_x = e.getX();
                stopDrag_y = e.getY();


                /*
                 * Iterator it = m_objects.iterator(); while(it.hasNext()){
                 * SceneItem item = (SceneItem)it.next(); if
                 * (item.getBounds().contains(startSelect_x, startSelect_x)){
                 * item.select(true); }else{ item.select(false); }
                }
                 */
                //  repaint();
            }
            //  System.out.println("Pressed");
        }

        public void mouseReleased(MouseEvent e) {
            m_draggedNow = "NULL";
            selectActivate = false;
            stopSelect_x = e.getX();
            stopSelect_y = e.getY();

            m_dragObjects = false;
            m_multiDragMode = false;
            repaint();
//System.out.println("Released");
        }

        public void mouseDragged(MouseEvent e) {

            stopSelect_x = e.getX();
            stopSelect_y = e.getY();


            m_dragObjects = true;


            repaint();
            //  System.out.println("Dragged");
        }

        public void mouseMoved(MouseEvent e) {
            //  repaint();
            // System.out.println("Moved");
        }
    }

    public class SelectEvent extends java.util.EventObject {

        protected Rectangle selectedRect;

        public SelectEvent(Object source, Rectangle selection) {

            super(source);
            selectedRect = selection;

        }
    }

    synchronized protected void fireSelectionHappened() {
        SelectEvent event;
        event = new SelectEvent((Object) this, m_selectionRect);
        Iterator i = m_objects.iterator();
        while (i.hasNext()) {
            SceneItem.SelectEventListener listener =
                    ((SceneItem) i.next()).getFirstListener();
            listener.selectionHappened(event);
        }
    }

    synchronized protected void fireSelectionCancelled() {
        SelectEvent event;
        event = new SelectEvent((Object) this, m_selectionRect);
        Iterator i = m_objects.iterator();
        while (i.hasNext()) {
            SceneItem.SelectEventListener listener =
                    ((SceneItem) i.next()).getFirstListener();
            listener.selectionCancelled(event);
        }
    }

    /**
     * Метод очистки диаграммы.
     */
    public void clear() {
        this.m_objects.clear();
        this.m_model.clear();
        this.repaint();
    }

    /**
     * Метод сохранения диаграммы в файл.
     *
     * @param filename Имя файла.
     */
    public void save(String filename) throws ParserConfigurationException, SAXException, IOException, TransformerConfigurationException, TransformerException {
        m_model.save(filename);
    }

    /**
     * Метод чтения диаграммы из файла.
     *
     * @param filename
     */
    public void load(String filename) throws ParserConfigurationException, SAXException, IOException {
        m_model.load(filename);
    }
}
