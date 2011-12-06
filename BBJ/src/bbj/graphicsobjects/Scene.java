/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import bbj.virtualobjects.*;
import bbj.graphicsobjects.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.awt.geom.Rectangle2D;
import java.util.*;

/**
 * Класс - сцена для отрисовки объектов диаграммы.
 * @version 1.0
 */
public final class Scene extends JPanel {

    private boolean m_isGrid;
    private int m_gridFactor = 20;
    private Color m_gridColor = new Color(128, 128, 128, 64);
    private UISelector m_messageSelector;
    private JPanel m_selectorsPanel;
    private VirtualModel m_model;
    private ArrayList<SceneItem> m_objects;
    private int m_messageSelector_x;
    private int m_messageSelector_y;
    private int m_entitySelector_x;
    private int m_entitySelector_y;
    private UISelector m_entitySelector;
    private String m_draggedNow;
    private ArrayList<String> itemsMessages;
    private ArrayList<String> itemsEntities;
    private boolean selectActivate;
    private int startSelect_x;
    private int startSelect_y;
    private int stopSelect_x;
    private int stopSelect_y;
    private int[] m_selectionArray_x;
    private int[] m_selectionArray_y;
    private Rectangle m_messageSelectorRect;
    private Rectangle m_entitySelectorRect;
    private Rectangle m_selectionRect;
    private ArrayList<SceneItem> m_selectionObjects;

    /**
     * Метод получения объекта сцены по индексу.
     * @param index Индекс получаемого объекта.
     * @return Объект сцены.
     */
    public SceneItem get(int index) {
        return m_objects.get(index);
    }

    /**
     *  Метод получения ссылки на модель.
     * @return Модель.
     */
    public VirtualModel getModel() {
        return m_model;
    }

    /**
     * Конструктор по умолчанию.
     */
    public Scene() {
        super();
        m_isGrid = true;
        m_model = new VirtualModel();
        m_objects = new ArrayList<SceneItem>();
        m_messageSelector_x = 10;
        m_messageSelector_y = 10;
        m_draggedNow = new String();
        selectActivate = false;
        startSelect_x = 0;
        startSelect_y = 0;
        stopSelect_x = 0;
        stopSelect_y = 0;
        m_selectionRect = new Rectangle();
        makeSelectors();

        this.setDoubleBuffered(true);
        m_selectionArray_x = new int[2];
        m_selectionArray_y = new int[2];
        m_selectionObjects = new ArrayList<SceneItem>();

        this.setToolTipText("Диаграмма последовательности");

        this.addMouseListener(new MouseSlot());    // Добавляем слушателя мыши на сцену

        this.addMouseMotionListener(new MouseSlot());



        UIFreeComment testCommentChecked = new UIFreeComment(350, 100,
                "Linux работает на множестве архитектур, таких как "
                + "Intel x86, x86-64, PowerPC, ARM, Alpha AXP, Sun SPARC, Motorola 68000,"
                + " Hitachi SuperH, IBM S/390, MIPS, HP PA-RISC,"
                + " AXIS CRIS, Renesas M32R, Atmel AVR32, Renesas H8/300, NEC V850, Tensilica Xtensa и многих других.");

        // Добавляем тестовые объекты в контейнер       

        UIFreeComment testCommentChecked1 = new UIFreeComment(333, 333,
                "Процессоры Power PC также используются в многоядерных"
                + " процессорах в качестве управляющих ядер, например:");


        this.add(testCommentChecked1);
        this.add(testCommentChecked);

        // Добавляем тестовые объекты в контейнер
        m_objects.add(testCommentChecked);
        m_objects.add(testCommentChecked1);


        // Создаем сцене особого слушателя
        SceneItemListener sceneItemListener = new SceneItemListener();

        // Задаем сцене слушателя
        this.addMouseListener(sceneItemListener);

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

    public Rectangle getUIPanelsRectangle() {
        Rectangle rect = m_messageSelector.getBounds();
        return rect;
    }

    @Override
    protected void paintComponent(Graphics g) {

        Graphics2D g2 = (Graphics2D) g;

        /*g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        g2.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
        g2.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_LCD_HRGB);
        g2.setRenderingHint(RenderingHints.KEY_ALPHA_INTERPOLATION, RenderingHints.VALUE_ALPHA_INTERPOLATION_QUALITY);
        g2.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BICUBIC);*/

        g2.setColor(Color.WHITE);
        g2.fillRect(0, 0, getWidth(), getHeight());


        if (m_isGrid) {
            makeGrid(g2);
        }


        //m_messageSelector.paintComponent(g);

        if (m_draggedNow.equals("Comment")) {
            g2.setColor(Color.RED);
            g2.fillRect(0, 0,
                    100, 100);

        }


        /* UIFreeComment testComment = new UIFreeComment(200,155,
        "abcd efghij klmnop \n qrstuvwxyz\n1234567890");
         */ 


      


        // Отрисовываем все объекты сцены
        Iterator<SceneItem> i = m_objects.iterator();



        UIFreeComment testCommentChecked1 = new UIFreeComment(300, 150,
                "qweqwe rere asdasdqqqqqqqq");




        while (i.hasNext()) {
            i.next().paint(g);
        }

        //recreateSelectors();

        //m_selectorsPanel.updateUI();

        if (selectActivate) {

            g2.setColor(new Color(0, 153, 255, 128));
            /* m_selectionArray_x[0]=startSelect_x;
            m_selectionArray_x[1]=stopSelect_x;
            m_selectionArray_y[0]=startSelect_y;
            m_selectionArray_y[1]=stopSelect_y;*/
            //g2.drawPolygon(m_selectionArray_x, m_selectionArray_y, 2);
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
            fireSelectionHappened();
        }

    }

    protected void makeGrid(Graphics g) {

        g.setColor(m_gridColor);
        int _height = this.getHeight();
        int _width = this.getWidth();
        for (int i = 0; i < 200; i++) {
            g.drawLine(0, m_gridFactor * i, _width, m_gridFactor * i); // Горизонтальные
        }
        for (int i = 0; i < 200; i++) {
            g.drawLine(m_gridFactor * i, 0, m_gridFactor * i, _height); // Вертикальные
        }

    }

    public void recreateSelectors() {
        m_messageSelector = new UISelector(
                itemsMessages,
                2,
                "images/48/",
                "images/24/",
                "images/16/",
                "message");
        m_entitySelector = new UISelector(
                itemsEntities,
                2,
                "images/48/",
                "images/24/",
                "images/16/",
                "entity");


        m_messageSelector.setLocation(m_messageSelector_x, m_messageSelector_y);
        m_entitySelector.setLocation(
                m_messageSelector_x,
                m_messageSelector_y + m_messageSelector.getHeight() + 10);

        //m_messageSelector.addMouseMotionListener(new MouseMotionSlot());
        m_entitySelector.addMouseMotionListener(new MouseSlot());

        this.add(m_messageSelector);
        this.add(m_entitySelector);

    }

    protected void makeSelectors() {
        itemsMessages = new ArrayList<String>();
        itemsMessages.add("Reply");
        itemsMessages.add("Create");
        itemsMessages.add("Message");
        itemsMessages.add("Delete");
        itemsMessages.add("Sync");
        itemsMessages.add("Async");


        itemsEntities = new ArrayList<String>();
        itemsEntities.add("Actor");
        itemsEntities.add("Comment");
        itemsEntities.add("LifeLine");

        m_messageSelector = new UISelector(
                itemsMessages,
                2,
                "images/48/",
                "images/24/",
                "images/16/",
                "message");
        m_entitySelector = new UISelector(
                itemsEntities,
                2,
                "images/48/",
                "images/24/",
                "images/16/",
                "entity");


        m_messageSelectorRect = m_messageSelector.getBounds();
        m_entitySelectorRect = m_entitySelector.getBounds();

        m_selectorsPanel = new JPanel();
        m_selectorsPanel.setSize(m_messageSelectorRect.width, m_messageSelectorRect.height
                + m_entitySelectorRect.height + 20);
        BoxLayout box = new BoxLayout(m_selectorsPanel, BoxLayout.Y_AXIS);
        m_selectorsPanel.setLayout(box);


        m_selectorsPanel.add(m_messageSelector);
        m_selectorsPanel.add(m_entitySelector);
        this.add(m_selectorsPanel);
        m_selectorsPanel.setLocation(m_messageSelector_x, m_messageSelector_y);
        /* m_messageSelector.setLocation(m_messageSelector_x, m_messageSelector_y);
        m_entitySelector.setLocation(
        m_messageSelector_x,
        m_messageSelector_y + m_messageSelector.getHeight() + 10);
         */
        //m_messageSelector.addMouseMotionListener(new MouseMotionSlot());
        m_entitySelector.addMouseMotionListener(new MouseSlot());


    }

    class MouseSlot implements MouseListener, MouseMotionListener {

        /**
         * Действие при клике мышью на сцену
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
            if (!m_messageSelectorRect.contains(e.getPoint())
                    && !m_entitySelectorRect.contains(e.getPoint())) {
                selectActivate = true;
                startSelect_x = e.getX();
                startSelect_y = e.getY();
                stopSelect_x = e.getX() + 2;
                stopSelect_y = e.getY() + 2;
                /*  Iterator it = m_objects.iterator();
                while(it.hasNext()){
                SceneItem item = (SceneItem)it.next();
                if (item.getBounds().contains(startSelect_x, startSelect_x)){
                item.select(true);
                }else{
                item.select(false);
                }
                }*/
                //  repaint();
            }
        }

        public void mouseReleased(MouseEvent e) {
            m_draggedNow = "NULL";
            selectActivate = false;
            repaint();

        }

        public void mouseDragged(MouseEvent e) {
            String owner = m_entitySelector.getOwner(e.getPoint());
            if ("Current".equals(owner)) {
                m_draggedNow = m_entitySelector.getSelected();
            }
            stopSelect_x = e.getX();
            stopSelect_y = e.getY();

            repaint();
        }

        public void mouseMoved(MouseEvent e) {
            stopSelect_x = e.getX();
            stopSelect_y = e.getY();
            repaint();
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
}
