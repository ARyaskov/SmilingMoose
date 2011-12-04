/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import bbj.virtualobjects.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;


/**
 * Класс - сцена для отрисовки объектов диаграммы.
 * @version 1.0
 */
public final class Scene extends JPanel {
    private boolean m_isGrid;
    private int m_gridFactor = 20;
    private Color m_gridColor = new Color(128,128,128,64);
    private UIMessageSelector m_messageSelector;
    private VirtualModel m_model;
    private ArrayList<SceneItem> m_objects;
    private int m_messageSelector_x;
    private int m_messageSelector_y;
    
    
    /**
     * Метод получения объекта сцены по индексу.
     * @param index Индекс получаемого объекта.
     * @return Объект сцены.
     */
    public SceneItem get (int index) {
        return m_objects.get(index);
    }
    
    /**
     * Конструктор по умолчанию.
     */
    public Scene(){
        super();
        m_isGrid = true;
        m_model = new VirtualModel();
        m_objects = new ArrayList<SceneItem>();
        m_messageSelector_x = 5;
        m_messageSelector_y = 5;
        
        makeSelectors();
        
    }

    public void setIsGrid(boolean _isGrid){
        m_isGrid = _isGrid;
        repaint();
    }
    public void setGridFactor(int factor){
        m_gridFactor = factor;
        repaint();
    }
    
    public void setGridColor(Color color){
        m_gridColor = color;
        repaint();
    }
    
    public Color getGridColor(){
        return m_gridColor;
    }
    
    public boolean getIsGrid(){
        return m_isGrid;
    }
    
    public int getGridFactor(){
        return m_gridFactor;
    }
    @Override
    protected void paintComponent(Graphics g) {
        
        g.setColor(Color.WHITE);
        g.fillRect(0, 0, getWidth(), getHeight());

         if (m_isGrid)
            makeGrid(g);
       
        
    
         makeSelectors();
         
        UIFreeComment testComment = new UIFreeComment(200,155,
                "abcd efghij klmnop \n qrstuvwxyz\n1234567890");
       UIFreeComment testCommentChecked = new UIFreeComment(300,75,
                "qweqwe rere asdasd");
       testCommentChecked.select(true);
       testComment.draw(g);
       testCommentChecked.draw(g);
         
        }
    
    protected void makeGrid(Graphics g){
      
        g.setColor(m_gridColor);
        int _height=this.getHeight();
        int _width=this.getWidth();
        for (int i=0;i<200;i++){
            g.drawLine(0, m_gridFactor*i, _width, m_gridFactor*i); // Горизонтальные
        }
        for (int i=0;i<200;i++){
            g.drawLine(m_gridFactor*i, 0, m_gridFactor*i, _height); // Вертикальные
        }

    }
    protected void makeSelectors(){
        
        m_messageSelector = new UIMessageSelector();
        m_messageSelector.setLocation(m_messageSelector_x, m_messageSelector_y);
        
        m_messageSelector.addMouseMotionListener(new MouseMotionSlot());
        this.add(m_messageSelector);
        
    }
    class MouseMotionSlot implements MouseMotionListener{
        public void mouseDragged(MouseEvent e) {
           
        }
         
        public void mouseMoved(MouseEvent e) {
             
        }

    }

}
