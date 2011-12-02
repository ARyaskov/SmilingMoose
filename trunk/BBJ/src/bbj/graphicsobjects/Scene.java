/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import bbj.virtualobjects.*;
import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;


/**
 * Класс - сцена для отрисовки объектов диаграммы.
 * @version 1.0
 */
public class Scene extends JPanel {
    private boolean isGrid;
    private int gridFactor = 20;
    private Color gridColor = new Color(128,128,128,64);
    
    private VirtualModel m_model;
    private ArrayList<Component> m_objects;
    
    public Scene(){
        super();
        isGrid = true;
        m_model = new VirtualModel();
        m_objects = new ArrayList<Component>();
        
        
    }
    
    @Override
    protected void paintComponent(Graphics g) {
            
            if (isGrid)
                makeGrid(g);
            //isGrid = false;
            //UILifeLine ll = new UILifeLine();
            //ll.paintComponent(g);
        }
    
    protected void makeGrid(Graphics g){
        g.setColor(gridColor);
        int _height=this.getHeight();
        int _width=this.getWidth();
        for (int i=0;i<200;i++){
            g.drawLine(0, gridFactor*i, _width, gridFactor*i); // Горизонтальные
        }
        for (int i=0;i<200;i++){
            g.drawLine(gridFactor*i, 0, gridFactor*i, _height); // Вертикальные
        }
        
    }
}
