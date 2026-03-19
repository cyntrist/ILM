using Unity.VisualScripting;
using UnityEditor;
using UnityEngine;
using UnityEngine.Rendering.Universal;

public class BlitMaterialFeature : ScriptableRendererFeature
{
    private BlitMaterialPass m_BlitMaterialPass;

    [SerializeField]
    private Material _material;

    [SerializeField]
    private RenderPassEvent _renderPassEvent;

    // se llama a esto cada vez que se cambia algo (incluyendo en su creación)
    public override void Create()
    {
        m_BlitMaterialPass = new BlitMaterialPass();
        m_BlitMaterialPass.renderPassEvent = _renderPassEvent;
    }

    // se llama una vez por frame
    public override void AddRenderPasses(ScriptableRenderer renderer, ref RenderingData renderingData)
    {
        if (_material == null)
            return; 

        m_BlitMaterialPass.Setup(_material);
        renderer.EnqueuePass(m_BlitMaterialPass);
    }
}
