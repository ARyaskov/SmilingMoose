/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import java.awt.*;


/**
 *
 * @author Alexander
 */
public class UIFocusControl extends SceneItem {

    /** Сообщение родитель */
    public UIMessage m_parentMessage;
    
    /** Является ли отправителем*/
    public boolean m_isSender;
    
    
    /**
     * Главный конструктор
     * Начальный размер 40х20
     */
    UIFocusControl(UIMessage parent, boolean isSender){
        m_parentMessage = parent;
        m_isSender = isSender;
        this.h = 40;
        this.w = 20;
        
        SceneItemListener listener = new SceneItemListener(this);

        this.addMouseListener(listener);
        this.addMouseMotionListener(listener);
        
       
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        
        
        
        Graphics2D g2 = (Graphics2D)g;
        
        if (m_isSender)
            this.x = m_parentMessage.x-10;

        else
            this.x = m_parentMessage.m_receiver.x+50;
        
        this.y = m_parentMessage.y;
        
        if (m_parentMessage.getClass().getName().equals("bbj.graphicsobjects.UICreateMessage" )){
            this.y = m_parentMessage.y+40;
        }
            
        
        
        //m_isSelected = m_parentMessage.isSelected();
        
        setBounds(x, y, w, h);
        
        g2.setStroke(new BasicStroke());
        
        g.setColor(Color.WHITE);
        
        Polygon p = new Polygon();          // Полигон комментария

        // Рисуем прямоугольник со скошенным уголком
        p.addPoint(x, y);
        p.addPoint(x + w, y);
        p.addPoint(x + w, y + h);
        p.addPoint(x, y + h);
        
        g.fillPolygon(p);
        
        if (m_isSelected)   // Если выбрали - заливаем желтым   
            g.setColor(Color.red);
        else                // Иначе, заливаем полигон голубоватым цветом
            g.setColor(Color.black);
        
        g.drawRect(x, y, w, h);
    }
    
    
    
    @Override
    protected void setDefaultName() {}
    
}
