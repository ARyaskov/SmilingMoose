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

/**
 * Класс - сцена для отрисовки объектов диаграммы.
 * @version 1.0
 */
public final class Scene extends JPanel {

    private boolean m_isGrid;
    private int m_gridFactor = 20;
    private Color m_gridColor = new Color(128, 128, 128, 64);
    private UISelector m_messageSelector;
    private VirtualModel m_model;
    private ArrayList<SceneItem> m_objects;
    private int m_messageSelector_x;
    private int m_messageSelector_y;
    private int m_entitySelector_x;
    private int m_entitySelector_y;
    private UISelector m_entitySelector;
    private String m_draggedNow;

    /**
     * Метод получения объекта сцены по индексу.
     * @param index Индекс получаемого объекта.
     * @return Объект сцены.
     */
    public SceneItem get(int index) {
        return m_objects.get(index);
    }

    /**
     * Конструктор по умолчанию.
     */
    public Scene() {
        super();
        m_isGrid = true;
        m_model = new VirtualModel();
        m_objects = new ArrayList<SceneItem>();
        m_messageSelector_x = 5;
        m_messageSelector_y = 5;
        m_draggedNow = new String();
        makeSelectors();


        this.addMouseListener(new MouseSlot());    // Добавляем слушателя мыши на сцену

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

    @Override
    protected void paintComponent(Graphics g) {

        g.setColor(Color.WHITE);
        g.fillRect(0, 0, getWidth(), getHeight());

        if (m_isGrid) {
            makeGrid(g);
        }

        //makeSelectors();
        m_messageSelector.paintComponent(g);

        if (m_draggedNow.equals("Comment")) {
            g.setColor(Color.RED);
            g.fillRect(0, 0,
                    100, 100);

        }
        makeSelectors();
        /* UIFreeComment testComment = new UIFreeComment(200,155,
        "abcd efghij klmnop \n qrstuvwxyz\n1234567890");
        */UIFreeComment testCommentChecked = new UIFreeComment(250,75,
        "qweqwe rere asdasdqqqqqqqq qqqqqqqqqq uuuuuuuuuu gggggggggggg" +
                "zzzzzzzzzzzz wwwwwwwwwwwww eeeeeeeeeeeeeee oooooooooooooo");

        testCommentChecked.select(false);
        
       
        UIFreeComment testCommentChecked1 = new UIFreeComment(300,150,
        "qweqwe rere asdasdqqqqqqqq");

        testCommentChecked1.select(true);
        testCommentChecked1.paint(g);
        testCommentChecked.paint(g);
        this.add(testCommentChecked);
        this.add(testCommentChecked1);
        // Добавляем тестовые объекты в контейнер
        m_objects.add(testCommentChecked);


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

    protected void makeSelectors() {
        ArrayList<String> itemsMessages = new ArrayList<String>();
        itemsMessages.add("Reply");
        itemsMessages.add("Create");
        itemsMessages.add("Message");
        itemsMessages.add("Delete");
        itemsMessages.add("Sync");
        itemsMessages.add("Async");

        m_messageSelector = new UISelector(
                itemsMessages,
                2,
                "images/48/",
                "images/24/",
                "images/16/",
                "message");

        ArrayList<String> itemsEntities = new ArrayList<String>();
        itemsEntities.add("Actor");
        itemsEntities.add("Comment");
        itemsEntities.add("LifeLine");
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
        }

        public void mouseReleased(MouseEvent e) {
            m_draggedNow = "NULL";

        }

        public void mouseDragged(MouseEvent e) {
            String owner = m_entitySelector.getOwner(e.getPoint());
            if ("Current".equals(owner)) {
                m_draggedNow = m_entitySelector.getSelected();
            }

        }

        public void mouseMoved(MouseEvent e) {
        }
    }
}
